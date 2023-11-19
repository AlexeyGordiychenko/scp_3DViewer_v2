#ifndef S21_3DVIEWER_V2_MODEL_H
#define S21_3DVIEWER_V2_MODEL_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

struct Vertex3d {
  double x;
  double y;
  double z;
};

class Model {
 public:
  void ParseFile(const std::string filename);
  void AffineMove(double ax, double ay, double az);
  void AffineRotateX(double angle);
  void AffineRotateY(double angle);
  void AffineRotateZ(double angle);
  void AffineScale(double k);

  void SetDimentionalValues();
  void TranslateToFromOrigin(int k);
  void MoveCenter(double ax, double ay, double az);
  void RestoreVertices();

 private:
  std::vector<Vertex3d> vertices;
  std::vector<Vertex3d> vertices_origin;
  std::vector<std::vector<int>> polygons;
  Vertex3d min_point = {0, 0, 0}, max_point = {0, 0, 0};
  double center_x = 0, center_y = 0, center_z = 0, size_coefficient = 0;

  void ClearData();
  void UpdateMinMaxPoints(Vertex3d point);
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_MODEL_H