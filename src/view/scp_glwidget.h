#ifndef SCP_3DVIEWER_V2_GLWIDGET_H
#define SCP_3DVIEWER_V2_GLWIDGET_H

#include <QOpenGLWidget>
#include <QtOpenGL>

#include "../utils/scp_enums.h"
#include "../utils/scp_observer.h"
#include "../utils/scp_vertex3d.h"

namespace scp {

class Controller;
class View;

class GLWidget : public QOpenGLWidget,
                 protected QOpenGLFunctions,
                 public Observer {
 public:
  // Constructors
  explicit GLWidget(QWidget* parent = nullptr);
  GLWidget(const GLWidget&) = delete;
  GLWidget& operator=(const GLWidget&) = delete;
  GLWidget(GLWidget&&) = delete;
  GLWidget& operator=(GLWidget&&) = delete;

  // Funcitons
  void ClearTransformations();
  void SetController(Controller* controller);
  void SetView(View* view);
  void UpdateObserver(EventType event) override;

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
  // Functions
  void SetProjection();
  void ApplyTransformations();
  void DrawPolygons();
  void DrawVertices();
  void NullifyView();
  ~GLWidget() override;

  // Variables
  int size_h_ = 0, size_w_ = 0;
  Vertex3d rotation_vertex_ = {0, 0, 0};
  Vertex3d translation_vertex_ = {0, 0, 0};
  double zoom_ = 1;
  QPointF last_mouse_pos_;
  Controller* controller_;
  View* view_;
};
}  // namespace scp
#endif  // SCP_3DVIEWER_V2_GLWIDGET_H
