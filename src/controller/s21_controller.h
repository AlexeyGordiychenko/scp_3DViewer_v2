#ifndef S21_3DVIEWER_V2_CONTROLLER_H
#define S21_3DVIEWER_V2_CONTROLLER_H

#include <string>
#include <vector>

#include "../utils/s21_vertex3d.h"
namespace s21 {

class Model;

class Controller {
 public:
  // Constructors and the destructor
  Controller(Model* model) : model_(model) {}
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  ~Controller();

  // Main functions
  void Initialize(const std::string filename);
  void RestoreVertices();

  void AffineMove(double ax, double ay, double az);
  void AffineRotate(double angle_x, double angle_y, double angle_z);
  void AffineScale(double k);

  size_t GetPolygonsEdgesCount() const;
  size_t GetVerticesCount() const;
  const std::vector<std::vector<int>>& GetPolygons() const;
  const std::vector<s21::Vertex3d>& GetVertices() const;

  double GetCenterX() const;
  double GetCenterY() const;
  double GetCenterZ() const;

  bool Empty() const;
  void NormalizeAngle(double& angle);

 private:
  Model* model_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_CONTROLLER_H
