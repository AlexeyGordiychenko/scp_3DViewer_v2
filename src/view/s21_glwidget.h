#ifndef S21_3DVIEWER_V2_GLWIDGET_H
#define S21_3DVIEWER_V2_GLWIDGET_H

#include <QOpenGLWidget>
#include <QtOpenGL>

#include "../controller/s21_controller.h"

namespace s21 {

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  // Constructors
  explicit GLWidget(QWidget* parent = nullptr);
  GLWidget(const GLWidget&) = delete;
  GLWidget& operator=(const GLWidget&) = delete;
  GLWidget(GLWidget&&) = delete;
  GLWidget& operator=(GLWidget&&) = delete;

  // Funcitons
  void SetProjectionType(int idx);
  void ClearTransformations();
  void SetController(Controller* controller);

  // Variables
  QColor bg_color_ = QColor(0, 0, 0);
  QColor line_color_ = QColor(0, 255, 0);
  QColor vertice_color_ = QColor(0, 0, 255);
  double edges_thickness_ = 1, vertice_size_ = 1;
  int vertice_type_ = 0, projection_type_ = 0, edges_type_ = 0;

 protected:
  // OPENGL
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  // Mouse events
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

 private:
  // Funcitons
  ~GLWidget() override;

  // Variables
  int size_h_ = 0, size_w_ = 0;
  Vertex3d rotation_vertex_ = {0, 0, 0};
  Vertex3d translation_vertex_ = {0, 0, 0};
  double zoom_ = 1;
  QPointF last_mouse_pos_;
  Controller* controller_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_GLWIDGET_H
