#include "s21_glwidget.h"

s21::GLWidget::~GLWidget() {}

s21::GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void s21::GLWidget::SetFilename(char *filename) { this->filename_ = filename; }

void s21::GLWidget::SetController(AbstractController *controller) {
  this->controller_ = controller;
}

void s21::GLWidget::SetProjectionType(int projectionType) {
  this->projectionType_ = projectionType;
}

void s21::GLWidget::RestoreVertices() { this->controller_->RestoreVertices(); }

void s21::GLWidget::Scale(double k) {
  if (k) {
    this->controller_->AffineScale(k);
  }
}

void s21::GLWidget::Move(double x, double y, double z) {
  if (x || y || z) {
    this->controller_->AffineMove(x, y, z);
  }
}

void s21::GLWidget::Rotate(double angle_x, double angle_y, double angle_z) {
  if (angle_x || angle_y || angle_z) {
    this->controller_->AffineRotateX(angle_x);
    this->controller_->AffineRotateY(angle_y);
    this->controller_->AffineRotateZ(angle_z);
    this->update();
  }
}

void s21::GLWidget::ClearTransformations() {
  this->x_rot_ = 0, this->y_rot_ = 0, this->z_rot_ = 0, this->x_trans_ = 0,
  this->y_trans_ = 0, this->zoom_ = 1;
}

void s21::GLWidget::ParseFile() {
  this->isParsed = false;
  this->ClearTransformations();
  this->controller_->Initialize(this->filename_);
  this->numVertices = this->controller_->GetVerticesCount();
  this->numEdges = this->controller_->GetPolygonsEdgesCount();
  this->isParsed = true;
  update();
}

void s21::GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void s21::GLWidget::resizeGL(int w, int h) {
  this->size_h_ = h;
  this->size_w_ = w;
  glViewport(0, 0, w, h);
}

void s21::GLWidget::paintGL() {
  glClearColor(bg_red_, bg_green_, bg_blue_, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  static double aspect_ratio =
      static_cast<double>(this->size_w_) / static_cast<double>(this->size_h_);

  if (this->isParsed) {
    if (this->projectionType_ == PARALLEL) {
      glOrtho(-1.5 * aspect_ratio, 1.5 * aspect_ratio, -1.5, 1.5, -2, 1000);
    } else {
      glFrustum(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, 99999);
      glTranslatef(0, 0, -2.5);
    }
    glScalef(this->zoom_, this->zoom_, this->zoom_);
    glTranslatef(this->controller_->GetCenterX() + this->x_trans_,
                 this->controller_->GetCenterY() + this->y_trans_,
                 this->controller_->GetCenterZ());
    glRotatef(this->x_rot_, 1.0, 0.0, 0.0);
    glRotatef(this->y_rot_, 0.0, 1.0, 0.0);
    glRotatef(this->z_rot_, 0.0, 0.0, 1.0);
    glTranslatef(-this->controller_->GetCenterX() - this->x_trans_,
                 -this->controller_->GetCenterY() - this->y_trans_,
                 -this->controller_->GetCenterZ());
    glTranslatef(this->x_trans_, this->y_trans_, 0.0);

    auto vertices = this->controller_->GetVertices();
    for (auto &polygon : this->controller_->GetPolygons()) {
      if (this->edges_type_ == DASHED) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
      }
      if (this->edges_type_ == SOLID) {
        glDisable(GL_LINE_STIPPLE);
      }
      glLineWidth(this->edges_thickness_);
      glColor3f(pol_red_, pol_green, pol_blue_);
      glBegin(GL_LINE_LOOP);
      for (auto vertex : polygon) {
        auto point = vertices[vertex];
        glVertex3d(point.x, point.y, point.z);
      }

      glEnd();
      if (this->vertice_type_ != NONE) {
        if (this->vertice_type_ == CIRCLE) {
          glEnable(GL_POINT_SMOOTH);
        } else {
          glDisable(GL_POINT_SMOOTH);
        }
        glPointSize(this->vertice_size_);
        glColor3f(ver_red_, ver_green_, ver_blue_);
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
  this->last_mouse_pos_ = event->position();
}

void normalizeAngle(double &angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360) angle -= 360 * 16;
}

void s21::GLWidget::mouseMoveEvent(QMouseEvent *event) {
  GLfloat dx = GLfloat(event->position().x() - this->last_mouse_pos_.x()) /
               this->size_w_;
  GLfloat dy = GLfloat(event->position().y() - this->last_mouse_pos_.y()) /
               this->size_h_;

  if (event->buttons() & Qt::LeftButton) {
    this->x_rot_ += 360 * dy;
    this->y_rot_ += 360 * dx;
    normalizeAngle(this->x_rot_);
    normalizeAngle(this->y_rot_);
  } else if (event->buttons() & Qt::RightButton) {
    this->x_rot_ += 360 * dy;
    this->z_rot_ += 360 * dx;
    normalizeAngle(this->x_rot_);
    normalizeAngle(this->z_rot_);
  } else if (event->buttons() & Qt::MiddleButton) {
    this->x_trans_ += dx;
    this->y_trans_ -= dy;
  }

  this->last_mouse_pos_ = event->position();
  update();
}

void s21::GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint angleDelta = event->angleDelta();

  if (!angleDelta.isNull()) {
    int delta = angleDelta.y();

    if (delta > 0) {
      this->zoom_ *= 1.1;
    } else {
      this->zoom_ /= 1.1;
    }
    update();
  }
}
