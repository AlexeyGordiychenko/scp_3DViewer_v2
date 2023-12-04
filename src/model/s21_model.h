#ifndef S21_3DVIEWER_V2_MODEL_H
#define S21_3DVIEWER_V2_MODEL_H

#include <string>
#include <vector>

#include "../utils/s21_affinedata.h"
#include "../utils/s21_vertex3d.h"

namespace s21 {

class Model {
 public:
  void Initialize(const std::string filename);
  void ParseFile(std::string filename);
  void RestoreVertices();

  void ApplyAffine(AffineData& data);
  void AffineMove(double ax, double ay, double az);
  void AffineRotateX(double angle);
  void AffineRotateY(double angle);
  void AffineRotateZ(double angle);
  void AffineScale(double k);

  size_t GetPolygonsEdgesCount() const;
  size_t GetVerticesCount() const;
  size_t GetPolygonsCount() const;
  const std::vector<int>& GetPolygons() const;
  const std::vector<double>& GetVertices() const;

  double GetCenterX() const;
  double GetCenterY() const;
  double GetCenterZ() const;

  bool Empty() const;

  void NormalizeAngle(double& angle);

 private:
  std::vector<double> vertices_;
  std::vector<double> vertices_origin_;
  std::vector<int> polygons_;
  s21::Vertex3d min_point_ = {0, 0, 0}, max_point_ = {0, 0, 0};
  double center_x_ = 0, center_y_ = 0, center_z_ = 0;
  bool is_empty_ = true;
  uint32_t polygons_edges_count_ = 0;

  void ClearData();
  bool ParseVertices(std::istringstream& iss);
  bool ParsePolygons(std::istringstream& iss);
  void UpdateMinMaxPoints(s21::Vertex3d point);
  void TranslateToOrigin();
  void SaveVertices();
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_MODEL_H