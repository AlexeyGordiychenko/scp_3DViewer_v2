#include "s21_controller.h"

#include "../model/s21_model.h"

s21::Controller::~Controller() {}

void s21::Controller::Initialize(const std::string filename) {
  model_->Initialize(filename);
}

void s21::Controller::RestoreVertices() { model_->RestoreVertices(); }

void s21::Controller::AffineMove(double ax, double ay, double az) {
  model_->AffineMove(ax, ay, az);
}

void s21::Controller::AffineRotate(double angle_x, double angle_y,
                                   double angle_z) {
  model_->AffineRotateX(angle_x);
  model_->AffineRotateY(angle_y);
  model_->AffineRotateZ(angle_z);
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

bool s21::Controller::Empty() const { return model_->Empty(); }

void s21::Controller::NormalizeAngle(double& angle) {
  model_->NormalizeAngle(angle);
}