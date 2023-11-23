#include "s21_controller.h"

#include "../model/s21_model.h"

void s21::Controller::Initialize(const std::string filename) {
  model_->Initialize(filename);
}

void s21::Controller::RestoreVertices() { model_->RestoreVertices(); }

void s21::Controller::AffineMove(double ax, double ay, double az) {
  model_->AffineMove(ax, ay, az);
}

void s21::Controller::AffineRotateX(double angle) {
  model_->AffineRotateX(angle);
}

void s21::Controller::AffineRotateY(double angle) {
  model_->AffineRotateY(angle);
}

void s21::Controller::AffineRotateZ(double angle) {
  model_->AffineRotateZ(angle);
}

void s21::Controller::AffineScale(double k) { model_->AffineScale(k); }

size_t s21::Controller::GetPolygonsEdgesCount() const {
  return model_->GetPolygonsEdgesCount();
}

size_t s21::Controller::GetVerticesCount() const {
  return model_->GetVerticesCount();
}

const std::vector<std::vector<int>>& s21::Controller::GetPolygons() const {
  return model_->GetPolygons();
}

const std::vector<s21::Vertex3d>& s21::Controller::GetVertices() const {
  return model_->GetVertices();
}

double s21::Controller::GetCenterX() const { return model_->GetCenterX(); }
double s21::Controller::GetCenterY() const { return model_->GetCenterY(); }
double s21::Controller::GetCenterZ() const { return model_->GetCenterZ(); }
