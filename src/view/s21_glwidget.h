#ifndef S21_3DVIEWER_V2_GLWIDGET_H
#define S21_3DVIEWER_V2_GLWIDGET_H

#include <QOpenGLWidget>
#include <QtOpenGL>

#include "../controller/s21_controller.h"

namespace s21 {

enum ProjectionType { kParallel, kCentral };
enum PolygonType { kSolid, kDashed };
enum VerticeType { kNone, kCircle, kSquare };

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  // Constructors
  explicit GLWidget(QWidget* parent = nullptr);
  GLWidget(const GLWidget&) = delete;
  GLWidget& operator=(const GLWidget&) = delete;
  GLWidget(GLWidget&&) = delete;
  GLWidget& operator=(GLWidget&&) = delete;

  // Funcitons
  void SetFilename(std::string filename);
  void SetController(AbstractController* controller);
  void SetProjectionType(int idx);
  void RestoreVertices();
  void Scale(double scale);
  void Move(double x, double y, double z);
  void Rotate(double angle_x, double angle_y, double angle_z);
  void ClearTransformations();
  void ParseFile();

  // Variables
  uint32_t num_vertices_ = 0, num_edges_ = 0;
  bool is_parsed = false, file_changed_ = true;
  double bg_red_ = 0, bg_green_ = 0, bg_blue_ = 0;
  double pol_red_ = 0, pol_green = 0, pol_blue_ = 0;
  double ver_red_ = 0, ver_green_ = 0, ver_blue_ = 0;
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
  void NormalizeAngle(double& angle);

  // Variables
  std::string filename_;
  int size_h_ = 0, size_w_ = 0;
  double x_rot_ = 0, y_rot_ = 0, z_rot_ = 0, x_trans_ = 0, y_trans_ = 0,
         zoom_ = 1;
  QPointF last_mouse_pos_;
  AbstractController* controller_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_GLWIDGET_H
