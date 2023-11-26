#include "s21_proxycontroller.h"

void s21::ProxyController::Initialize(const std::string filename) {
  real_controller_->Initialize(filename);
}

void s21::ProxyController::RestoreVertices() { real_controller_->RestoreVertices(); }

void s21::ProxyController::AffineMove(double ax, double ay, double az) {
  real_controller_->AffineMove(ax, ay, az);
}

void s21::ProxyController::AffineRotateX(double angle) {
  real_controller_->AffineRotateX(angle);
}

void s21::ProxyController::AffineRotateY(double angle) {
  real_controller_->AffineRotateY(angle);
}

void s21::ProxyController::AffineRotateZ(double angle) {
  real_controller_->AffineRotateZ(angle);
}

void s21::ProxyController::AffineScale(double k) { real_controller_->AffineScale(k); }

size_t s21::ProxyController::GetPolygonsEdgesCount() const {
  return real_controller_->GetPolygonsEdgesCount();
}

size_t s21::ProxyController::GetVerticesCount() const {
  return real_controller_->GetVerticesCount();
}

const std::vector<std::vector<int>>& s21::ProxyController::GetPolygons() const {
  return real_controller_->GetPolygons();
}

const std::vector<s21::Vertex3d>& s21::ProxyController::GetVertices() const {
  return real_controller_->GetVertices();
}

double s21::ProxyController::GetCenterX() const { return real_controller_->GetCenterX(); }
double s21::ProxyController::GetCenterY() const { return real_controller_->GetCenterY(); }
double s21::ProxyController::GetCenterZ() const { return real_controller_->GetCenterZ(); }
