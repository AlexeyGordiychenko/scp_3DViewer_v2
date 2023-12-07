#ifndef SCP_3DVIEWER_V2_CONTROLLER_H
#define SCP_3DVIEWER_V2_CONTROLLER_H

#include <string>
#include <vector>

#include "../utils/scp_affinedata.h"
#include "../utils/scp_vertex3d.h"

namespace scp {

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
  void ApplyAffine(AffineData& data);

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
  Model* model_;
};
}  // namespace scp
#endif  // SCP_3DVIEWER_V2_CONTROLLER_H
