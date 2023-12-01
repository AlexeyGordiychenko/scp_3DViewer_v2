#include "s21_glwidget.h"

#include "s21_enums.h"

s21::GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void s21::GLWidget::SetController(Controller* controller) {
  this->controller_ = controller;
}

void s21::GLWidget::SetProjectionType(int projection_type) {
  projection_type_ = projection_type;
}

void s21::GLWidget::ClearTransformations() {
  rotation_vertex_ = {0, 0, 0};
  translation_vertex_ = {0, 0, 0};
  zoom_ = 1;
}

void s21::GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void s21::GLWidget::resizeGL(int w, int h) {
  size_h_ = h;
  size_w_ = w;
  glViewport(0, 0, w, h);
}

void s21::GLWidget::paintGL() {
  glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  static double aspect_ratio =
      static_cast<double>(size_w_) / static_cast<double>(size_h_);

  if (!controller_->Empty()) {
    if (projection_type_ == kParallel) {
      glOrtho(-1.5 * aspect_ratio, 1.5 * aspect_ratio, -1.5, 1.5, -2, 1000);
    } else {
      glFrustum(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, 99999);
      glTranslatef(0, 0, -2.5);
    }
    glScalef(zoom_, zoom_, zoom_);
    glTranslatef(controller_->GetCenterX() + translation_vertex_.x,
                 controller_->GetCenterY() + translation_vertex_.y,
                 controller_->GetCenterZ());
    glRotatef(rotation_vertex_.x, 1.0, 0.0, 0.0);
    glRotatef(rotation_vertex_.y, 0.0, 1.0, 0.0);
    glRotatef(rotation_vertex_.z, 0.0, 0.0, 1.0);
    glTranslatef(-controller_->GetCenterX() - translation_vertex_.x,
                 -controller_->GetCenterY() - translation_vertex_.y,
                 -controller_->GetCenterZ());
    glTranslatef(translation_vertex_.x, translation_vertex_.y, 0.0);

    auto vertices = controller_->GetVertices();
    for (auto& polygon : controller_->GetPolygons()) {
      if (edges_type_ == kDashed) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
      }
      if (edges_type_ == kSolid) {
        glDisable(GL_LINE_STIPPLE);
      }
      glLineWidth(edges_thickness_);
      glColor3f(line_color_.redF(), line_color_.greenF(), line_color_.blueF());
      glBegin(GL_LINE_LOOP);
      for (auto vertex : polygon) {
        auto point = vertices[vertex];
        glVertex3d(point.x, point.y, point.z);
      }

      glEnd();
      if (vertice_type_ != kNone) {
        if (vertice_type_ == kCircle) {
          glEnable(GL_POINT_SMOOTH);
        } else {
          glDisable(GL_POINT_SMOOTH);
        }
        glPointSize(vertice_size_);
        glColor3f(vertice_color_.redF(), vertice_color_.greenF(),
                  vertice_color_.blueF());
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

void s21::GLWidget::mousePressEvent(QMouseEvent* event) {
  last_mouse_pos_ = event->position();
}

void s21::GLWidget::mouseMoveEvent(QMouseEvent* event) {
  GLfloat dx = GLfloat(event->position().x() - last_mouse_pos_.x()) / size_w_;
  GLfloat dy = GLfloat(event->position().y() - last_mouse_pos_.y()) / size_h_;

  if (event->buttons() & Qt::LeftButton) {
    rotation_vertex_.x += 360 * dy;
    rotation_vertex_.y += 360 * dx;
    controller_->NormalizeAngle(rotation_vertex_.x);
    controller_->NormalizeAngle(rotation_vertex_.y);
  } else if (event->buttons() & Qt::RightButton) {
    rotation_vertex_.x += 360 * dy;
    rotation_vertex_.z += 360 * dx;
    controller_->NormalizeAngle(rotation_vertex_.x);
    controller_->NormalizeAngle(rotation_vertex_.z);
  } else if (event->buttons() & Qt::MiddleButton) {
    translation_vertex_.x += dx;
    translation_vertex_.y -= dy;
  }

  last_mouse_pos_ = event->position();
  update();
}

void s21::GLWidget::wheelEvent(QWheelEvent* event) {
  QPoint angleDelta = event->angleDelta();

  if (!angleDelta.isNull()) {
    int delta = angleDelta.y();

    if (delta > 0) {
      zoom_ *= 1.1;
    } else {
      zoom_ /= 1.1;
    }
    update();
  }
}

s21::GLWidget::~GLWidget() {}
