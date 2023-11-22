#include "s21_glwidget.h"

s21::GLWidget::~GLWidget() {}

s21::GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void s21::GLWidget::setFilename(char *filename) { this->filename = filename; }

void s21::GLWidget::setController(s21::Controller *controller) {
  this->controller = controller;
}

void s21::GLWidget::setProjectionType(int projectionType) {
  this->projectionType = projectionType;
}

void s21::GLWidget::RestoreVertices() { this->controller->RestoreVertices(); }

void s21::GLWidget::scale(double k) {
  if (k) {
    this->controller->AffineScale(k);
  }
}

void s21::GLWidget::move(double x, double y, double z) {
  if (x || y || z) {
    this->controller->AffineMove(x, y, z);
  }
}

void s21::GLWidget::rotate(double angle_x, double angle_y, double angle_z) {
  if (angle_x || angle_y || angle_z) {
    this->controller->AffineRotateX(angle_x);
    this->controller->AffineRotateY(angle_y);
    this->controller->AffineRotateZ(angle_z);
    this->update();
  }
}

void s21::GLWidget::clearTransformations() {
  this->xRot = 0, this->yRot = 0, this->zRot = 0, this->xTrans = 0,
  this->yTrans = 0, this->zoom = 1;
}

void s21::GLWidget::parseFile() {
  this->isParsed = false;
  this->clearTransformations();
  this->controller->Initialize(this->filename);
  this->numVertices = this->controller->GetVerticesCount();
  this->numEdges = this->controller->GetPolygonsEdgesCount();
  this->isParsed = true;
  update();
}

void s21::GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void s21::GLWidget::resizeGL(int w, int h) {
  this->sizeH = h;
  this->sizeW = w;
  glViewport(0, 0, w, h);
}

void s21::GLWidget::paintGL() {
  glClearColor(bg_red, bg_green, bg_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  static double aspect_ratio =
      static_cast<double>(this->sizeW) / static_cast<double>(this->sizeH);

  if (this->isParsed) {
    if (this->projectionType == PARALLEL) {
      glOrtho(-1.5 * aspect_ratio, 1.5 * aspect_ratio, -1.5, 1.5, -2, 1000);
    } else {
      glFrustum(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, 99999);
      glTranslatef(0, 0, -2.5);
    }
    glScalef(this->zoom, this->zoom, this->zoom);
    glTranslatef(this->controller->GetCenterX() + this->xTrans,
                 this->controller->GetCenterY() + this->yTrans,
                 this->controller->GetCenterZ());
    glRotatef(this->xRot, 1.0, 0.0, 0.0);
    glRotatef(this->yRot, 0.0, 1.0, 0.0);
    glRotatef(this->zRot, 0.0, 0.0, 1.0);
    glTranslatef(-this->controller->GetCenterX() - this->xTrans,
                 -this->controller->GetCenterY() - this->yTrans,
                 -this->controller->GetCenterZ());
    glTranslatef(this->xTrans, this->yTrans, 0.0);

    auto vertices = this->controller->GetVertices();
    for (auto &polygon : this->controller->GetPolygons()) {
      if (this->edges_type == DASHED) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
      }
      if (this->edges_type == SOLID) {
        glDisable(GL_LINE_STIPPLE);
      }
      glLineWidth(this->edges_thickness);
      glColor3f(pol_red, pol_green, pol_blue);
      glBegin(GL_LINE_LOOP);
      for (auto vertex : polygon) {
        auto point = vertices[vertex];
        glVertex3d(point.x, point.y, point.z);
      }

      glEnd();
      if (this->vertice_type != NONE) {
        if (this->vertice_type == CIRCLE) {
          glEnable(GL_POINT_SMOOTH);
        } else {
          glDisable(GL_POINT_SMOOTH);
        }
        glPointSize(this->vertice_size);
        glColor3f(ver_red, ver_green, ver_blue);
        glBegin(GL_POINTS);
        for (auto vertex : polygon) {
          auto point = vertices[vertex];
          glVertex3d(point.x, point.y, point.z);
        }
        glEnd();
      }
    }
    glFlush();
  }
}

void s21::GLWidget::mousePressEvent(QMouseEvent *event) {
  this->lastMousePos = event->position();
}

void normalizeAngle(double &angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360) angle -= 360 * 16;
}

void s21::GLWidget::mouseMoveEvent(QMouseEvent *event) {
  GLfloat dx =
      GLfloat(event->position().x() - this->lastMousePos.x()) / this->sizeW;
  GLfloat dy =
      GLfloat(event->position().y() - this->lastMousePos.y()) / this->sizeH;

  if (event->buttons() & Qt::LeftButton) {
    this->xRot += 360 * dy;
    this->yRot += 360 * dx;
    normalizeAngle(this->xRot);
    normalizeAngle(this->yRot);
  } else if (event->buttons() & Qt::RightButton) {
    this->xRot += 360 * dy;
    this->zRot += 360 * dx;
    normalizeAngle(this->xRot);
    normalizeAngle(this->zRot);
  } else if (event->buttons() & Qt::MiddleButton) {
    this->xTrans += dx;
    this->yTrans -= dy;
  }

  this->lastMousePos = event->position();
  update();
}

void s21::GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint angleDelta = event->angleDelta();

  if (!angleDelta.isNull()) {
    int delta = angleDelta.y();

    if (delta > 0) {
      this->zoom *= 1.1;
    } else {
      this->zoom /= 1.1;
    }
    update();
  }
}
