#ifndef S21_PROXYProxyController_H
#define S21_PROXYProxyController_H

#include "../controller/s21_abstractcontroller.h"
#include "QStringList"
#include "s21_view.h"
#include "string"

namespace s21 {
class ProxyController : public AbstractController, public QObject {
public:
  // Constructors and the destructor
  ProxyController(AbstractController *controller, View *view);
  ProxyController(const ProxyController &) = delete;
  ProxyController &operator=(const ProxyController &) = delete;
  ProxyController(ProxyController &&) = delete;
  ProxyController &operator=(ProxyController &&) = delete;
  ~ProxyController() = default;

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
  const std::vector<std::vector<int>> &GetPolygons() const override;
  const std::vector<s21::Vertex3d> &GetVertices() const override;

  double GetCenterX() const override;
  double GetCenterY() const override;
  double GetCenterZ() const override;

private:
  AbstractController *real_controller_;
  View *view_;

private slots:
  void InitializeRecent(const std::string filename);
};
} // namespace s21

#endif // S21_PROXYProxyController_H
