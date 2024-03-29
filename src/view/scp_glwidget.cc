#include "scp_glwidget.h"

#include "../controller/scp_controller.h"
#include "../utils/scp_enums.h"
#include "scp_view.h"

scp::GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void scp::GLWidget::SetController(Controller* controller) {
  controller_ = controller;
}

void scp::GLWidget::SetView(View* view) {
  view_ = view;
  view_->AddObserver(this);
  connect(view_, &View::die, this, &GLWidget::NullifyView);
}

void scp::GLWidget::UpdateObserver(EventType event) {
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

void scp::GLWidget::ClearTransformations() {
  rotation_vertex_ = {0, 0, 0};
  translation_vertex_ = {0, 0, 0};
  zoom_ = 1;
}

void scp::GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void scp::GLWidget::resizeGL(int w, int h) {
  size_h_ = h;
  size_w_ = w;
  glViewport(0, 0, w, h);
}

void scp::GLWidget::paintGL() {
  // Set BG color
  auto bg_color = view_->GetBackgroundColor();
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (!controller_->Empty()) {
    SetProjection();
    glVertexPointer(3, GL_DOUBLE, 0, controller_->GetVertices().data());
    glEnableClientState(GL_VERTEX_ARRAY);
    ApplyTransformations();
    DrawPolygons();
    DrawVertices();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void scp::GLWidget::mousePressEvent(QMouseEvent* event) {
  last_mouse_pos_ = event->position();
}

void scp::GLWidget::mouseMoveEvent(QMouseEvent* event) {
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
    translation_vertex_.x += dx * 2;
    translation_vertex_.y -= dy * 2;
  }

  last_mouse_pos_ = event->position();
  update();
}

void scp::GLWidget::wheelEvent(QWheelEvent* event) {
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

void scp::GLWidget::SetProjection() {
  static double aspect_ratio =
      static_cast<double>(size_w_) / static_cast<double>(size_h_);

  if (view_->GetProjectionType() == kParallel) {
    glOrtho(-1.5 * aspect_ratio, 1.5 * aspect_ratio, -1.5, 1.5, -2, 1000);
  } else {
    glFrustum(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, 99999);
    glTranslatef(0, 0, -2.5);
  }
}
void scp::GLWidget::ApplyTransformations() {
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
}

void scp::GLWidget::DrawPolygons() {
  auto line_color = view_->GetLineColor();
  auto line_type = view_->GetLineType();
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
}

void scp::GLWidget::DrawVertices() {
  auto vertice_color = view_->GetVerticeColor();
  auto vertice_type = view_->GetVerticeType();
  auto vertice_size = view_->GetVerticeSize();

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
}

void scp::GLWidget::NullifyView() { view_ = nullptr; }

scp::GLWidget::~GLWidget() {
  if (view_) view_->RemoveObserver(this);
}
