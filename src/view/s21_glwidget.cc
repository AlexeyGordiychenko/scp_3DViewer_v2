#include "s21_glwidget.h"

#include "../controller/s21_controller.h"
#include "../utils/s21_enums.h"
#include "s21_view.h"

s21::GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void s21::GLWidget::SetController(Controller* controller) {
  controller_ = controller;
}

void s21::GLWidget::SetView(View* view) {
  view_ = view;
  view_->AddObserver(this);
}

void s21::GLWidget::UpdateObserver(EventType event) {
  switch (event) {
    case EventType::kRenderFile:
    case EventType::kSetAffine:
      ClearTransformations();
      update();
      break;
    case EventType::kAppearanceChange:
    case EventType::kSetProjectionType:
    case EventType::kLoadSettings:
      update();
    default:
      break;
  }
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
  auto bg_color = view_->GetBackgroundColor();
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  static double aspect_ratio =
      static_cast<double>(size_w_) / static_cast<double>(size_h_);

  if (!controller_->Empty()) {
    glVertexPointer(3, GL_DOUBLE, 0, controller_->GetVertices().data());
    glEnableClientState(GL_VERTEX_ARRAY);

    if (view_->GetProjectionType() == kParallel) {
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

    auto line_color = view_->GetLineColor();
    auto vertice_color = view_->GetVerticeColor();
    auto line_type = view_->GetLineType();
    auto vertice_type = view_->GetVerticeType();
    auto vertice_size = view_->GetVerticeSize();
    auto line_thickness = view_->GetLineThickness();

    if (line_type == kDashed) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00FF);
    }
    if (line_type == kSolid) {
      glDisable(GL_LINE_STIPPLE);
    }
    glLineWidth(line_thickness);
    glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());
    glDrawElements(GL_LINES, controller_->GetPolygonsCount(), GL_UNSIGNED_INT,
                   controller_->GetPolygons().data());

    if (vertice_type != kNone) {
      if (vertice_type == kCircle) {
        glEnable(GL_POINT_SMOOTH);
      } else {
        glDisable(GL_POINT_SMOOTH);
      }
      glPointSize(vertice_size);
      glColor3f(vertice_color.redF(), vertice_color.greenF(),
                vertice_color.blueF());
      glDrawArrays(GL_POINTS, 0, controller_->GetVerticesCount());
    }
    glDisableClientState(GL_VERTEX_ARRAY);
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
