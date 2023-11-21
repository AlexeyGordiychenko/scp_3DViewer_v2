#ifndef S21_3DVIEWER_V2_MODEL_H
#define S21_3DVIEWER_V2_MODEL_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "s21_vertex3d.h"

namespace s21 {

class Model {
 public:
  void Initialize(const std::string filename);
  void RestoreVertices();

  void AffineMove(double ax, double ay, double az);
  void AffineRotateX(double angle);
  void AffineRotateY(double angle);
  void AffineRotateZ(double angle);
  void AffineScale(double k);

  size_t GetPolygonsEdgesCount() const;
  size_t GetVerticesCount() const;
  const std::vector<std::vector<int>>& GetPolygons() const;
  const std::vector<s21::Vertex3d>& GetVertices() const;

 private:
  std::vector<s21::Vertex3d> vertices;
  std::vector<s21::Vertex3d> vertices_origin;
  std::vector<std::vector<int>> polygons;
  s21::Vertex3d min_point = {0, 0, 0}, max_point = {0, 0, 0};

  void ClearData();
  void ParseFile(std::ifstream& file);
  void UpdateMinMaxPoints(s21::Vertex3d point);
  void TranslateToOrigin();
  void SaveVertices();
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_MODEL_H