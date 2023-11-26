#ifndef S21_PROXYProxyController_H
#define S21_PROXYProxyController_H

#include "QStringList"
#include "string"
#include "../controller/s21_abstractcontroller.h"
#include "s21_view.h"

namespace s21 {
class ProxyController : public AbstractController
{
public:
 // Constructors and the destructor
 ProxyController(AbstractController* controller, View* view);
 ProxyController(const ProxyController&) = delete;
 ProxyController& operator=(const ProxyController&) = delete;
 ProxyController(ProxyController&&) = delete;
 ProxyController& operator=(ProxyController&&) = delete;
 ~ProxyController();

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
 AbstractController* real_controller_;
 //std::list<std::string> paths_;
 QStringList paths_;

 View* view_;
};
}

#endif // S21_PROXYProxyController_H

