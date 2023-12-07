#include "scp_controller.h"

#include "../model/scp_model.h"

scp::Controller::~Controller() {}

void scp::Controller::Initialize(const std::string filename) {
  model_->Initialize(filename);
}

void scp::Controller::RestoreVertices() { model_->RestoreVertices(); }

void scp::Controller::ApplyAffine(AffineData& data) {
  model_->ApplyAffine(data);
}

size_t scp::Controller::GetPolygonsEdgesCount() const {
  return model_->GetPolygonsEdgesCount();
}

size_t scp::Controller::GetVerticesCount() const {
  return model_->GetVerticesCount();
}

size_t scp::Controller::GetPolygonsCount() const {
  return model_->GetPolygonsCount();
}

const std::vector<int>& scp::Controller::GetPolygons() const {
  return model_->GetPolygons();
}

const std::vector<double>& scp::Controller::GetVertices() const {
  return model_->GetVertices();
}

double scp::Controller::GetCenterX() const { return model_->GetCenterX(); }
double scp::Controller::GetCenterY() const { return model_->GetCenterY(); }
double scp::Controller::GetCenterZ() const { return model_->GetCenterZ(); }

bool scp::Controller::Empty() const { return model_->Empty(); }

void scp::Controller::NormalizeAngle(double& angle) {
  model_->NormalizeAngle(angle);
}