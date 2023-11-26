#ifndef S21_3DVIEWER_V2_CONTROLLER_H
#define S21_3DVIEWER_V2_CONTROLLER_H

#include <string>
#include <vector>

#include "../model/s21_vertex3d.h"
#include "s21_abstractcontroller.h"

namespace s21 {

class Model;

class Controller : public AbstractController {
 public:
  // Constructors and the destructor
  Controller(Model* model) : model_(model) {}
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  ~Controller() = default;

  // Main functions
  void Initialize(const std::string filename) override;
  void RestoreVertices() override;

  void AffineMove(double ax, double ay, double az) override;
  void AffineRotateX(double angle) override;
  void AffineRotateY(double angle) override;
  void AffineRotateZ(double angle) override;
  void AffineScale(double k) override;

  size_t GetPolygonsEdgesCount() const override;
  size_t GetVerticesCount() const override;
  const std::vector<std::vector<int>>& GetPolygons() const override;
  const std::vector<s21::Vertex3d>& GetVertices() const override;

  double GetCenterX() const override;
  double GetCenterY() const override;
  double GetCenterZ() const override;

 private:
  Model* model_;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_CONTROLLER_H
