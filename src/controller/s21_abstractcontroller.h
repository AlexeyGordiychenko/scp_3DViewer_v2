#ifndef S21_3DVIEWER_V2_ABSTRACTCONTROLLER_H
#define S21_3DVIEWER_V2_ABSTRACTCONTROLLER_H

#include <string>
#include <vector>

#include "../model/s21_vertex3d.h"

namespace s21 {

class AbstractController {
 public:
  virtual ~AbstractController() = default;

  // Main functions
  virtual void Initialize(const std::string filename) = 0;
  virtual void RestoreVertices() = 0;

  virtual void AffineMove(double ax, double ay, double az) = 0;
  virtual void AffineRotateX(double angle) = 0;
  virtual void AffineRotateY(double angle) = 0;
  virtual void AffineRotateZ(double angle) = 0;
  virtual void AffineScale(double k) = 0;

  virtual size_t GetPolygonsEdgesCount() const = 0;
  virtual size_t GetVerticesCount() const = 0;
  virtual const std::vector<std::vector<int>>& GetPolygons() const = 0;
  virtual const std::vector<s21::Vertex3d>& GetVertices() const = 0;

  virtual double GetCenterX() const = 0;
  virtual double GetCenterY() const = 0;
  virtual double GetCenterZ() const = 0;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_CONTROLLER_H
