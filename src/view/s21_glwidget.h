#ifndef S21_3DVIEWER_V2_GLWIDGET_H
#define S21_3DVIEWER_V2_GLWIDGET_H

// #define GL_SILENCE_DEPRECATION
// #include <GL/gl.h>
// #include <GL/glut.h>

#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../controller/s21_controller.h"
#include "../model/s21_vertex3d.h"

namespace s21 {

enum projectionType { PARALLEL, CENTRAL };
enum polygonType { SOLID, DASHED };
enum verticeType { NONE, CIRCLE, SQUARE };

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit GLWidget(QWidget *parent = Q_NULLPTR);
  uint32_t numVertices = 0, numEdges = 0;
  bool isParsed = false, fileChanged = true;
  void SetFilename(char *filename);
  void SetProjectionType(int idx);
  void ParseFile();
  void RestoreVertices();
  void Scale(double scale);
  void Move(double x, double y, double z);
  void Rotate(double angle_x, double angle_y, double angle_z);
  void ClearTransformations();
  void SetController(AbstractController *controller);
  double bg_red_ = 0, bg_green_ = 0, bg_blue_ = 0;
  double pol_red_ = 0, pol_green = 0, pol_blue_ = 0;
  double ver_red_ = 0, ver_green_ = 0, ver_blue_ = 0;
  double edges_thickness_ = 1, vertice_size_ = 1;
  int vertice_type_ = 0, projectionType_ = 0, edges_type_ = 0;

 private:
  ~GLWidget() override;
  char *filename_;
  int size_h_ = 0, size_w_ = 0;
  double x_rot_ = 0, y_rot_ = 0, z_rot_ = 0, x_trans_ = 0, y_trans_ = 0,
         zoom_ = 1;
  QPointF last_mouse_pos_;
  AbstractController *controller_;

  void SetDimentionalValues();
  void CountVerticesEdges();

 protected:
  // OPENGL
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_GLWIDGET_H
