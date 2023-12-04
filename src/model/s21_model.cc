#include "s21_model.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

void s21::Model::Initialize(const std::string filename) {
  ParseFile(filename);
  TranslateToOrigin();
  SaveVertices();
}

void s21::Model::RestoreVertices() {
  vertices_ = vertices_origin_;
  center_x_ = 0;
  center_y_ = 0;
  center_z_ = 0;
}

void s21::Model::ApplyAffine(AffineData& data) {
  AffineScale(data.scale_k);
  AffineMove(data.move_x, data.move_y, data.move_z);
  AffineRotateX((data.rotate_x) * M_PI / 180);
  AffineRotateY((data.rotate_y) * M_PI / 180);
  AffineRotateZ((data.rotate_z) * M_PI / 180);
}

void s21::Model::AffineMove(double ax, double ay, double az) {
  if (!ax && !ay && !az) return;

  for (size_t i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] += ax;
    vertices_[i + 1] += ay;
    vertices_[i + 2] += az;
  }
  center_x_ += ax;
  center_y_ += ay;
  center_z_ += az;
}

void s21::Model::AffineRotateX(double angle) {
  if (!angle) return;

  double cos_angle = cos(angle), sin_angle = sin(angle);
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_y = vertices_[i + 1] - center_y_,
           temp_z = vertices_[i + 2] - center_z_;
    vertices_[i + 1] = temp_y * cos_angle - temp_z * sin_angle + center_y_;
    vertices_[i + 2] = temp_y * sin_angle + temp_z * cos_angle + center_z_;
  }
}

void s21::Model::AffineRotateY(double angle) {
  if (!angle) return;
  double cos_angle = cos(angle), sin_angle = sin(angle);
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_x = vertices_[i] - center_x_,
           temp_z = vertices_[i + 2] - center_z_;
    vertices_[i] = temp_x * cos_angle - temp_z * sin_angle + center_x_;
    vertices_[i + 2] = temp_x * sin_angle + temp_z * cos_angle + center_z_;
  }
}

void s21::Model::AffineRotateZ(double angle) {
  if (!angle) return;
  double cos_angle = cos(angle), sin_angle = sin(angle);
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_x = vertices_[i] - center_x_,
           temp_y = vertices_[i + 1] - center_y_;
    vertices_[i] = temp_x * cos_angle - temp_y * sin_angle + center_x_;
    vertices_[i + 1] = temp_x * sin_angle + temp_y * cos_angle + center_y_;
  }
}

void s21::Model::AffineScale(double k) {
  k = (k == 0) ? 1 : k;
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] *= k;
    vertices_[i + 1] *= k;
    vertices_[i + 2] *= k;
  }
}

size_t s21::Model::GetPolygonsEdgesCount() const {
  return polygons_edges_count_;
}

size_t s21::Model::GetVerticesCount() const { return vertices_.size() / 3; }

size_t s21::Model::GetPolygonsCount() const { return polygons_.size(); }

const std::vector<int>& s21::Model::GetPolygons() const { return polygons_; }

const std::vector<double>& s21::Model::GetVertices() const { return vertices_; }

double s21::Model::GetCenterX() const { return center_x_; }
double s21::Model::GetCenterY() const { return center_y_; }
double s21::Model::GetCenterZ() const { return center_z_; }

bool s21::Model::Empty() const { return is_empty_; }

void s21::Model::NormalizeAngle(double& angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360) angle -= 360 * 16;
}

void s21::Model::ClearData() {
  is_empty_ = true;
  vertices_.clear();
  polygons_.clear();
  min_point_ = {0, 0, 0};
  max_point_ = {0, 0, 0};
  center_x_ = 0, center_y_ = 0, center_z_ = 0;
}

void s21::Model::ParseFile(std::string filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file.");
  }

  ClearData();

  std::string line;
  size_t line_num = 0;
  polygons_edges_count_ = 0;
  while (std::getline(file, line) && ++line_num) {
    std::istringstream iss(line);
    std::string prefix;
    if (iss >> prefix) {
      if (prefix == "v") {
        if (!ParseVertices(iss)) {
          throw std::runtime_error("Line: " + std::to_string(line_num) +
                                   " failed to read a vertex.");
        }
      } else if (prefix == "f") {
        if (!ParsePolygons(iss)) {
          throw std::runtime_error("Line: " + std::to_string(line_num) +
                                   " failed to read a polygon.");
        }
      }
    }
  }
  file.close();
  is_empty_ = false;
}

bool s21::Model::ParseVertices(std::istringstream& iss) {
  Vertex3d point;
  bool res = false;
  if (iss >> point.x >> point.y >> point.z) {
    vertices_.push_back(point.x);
    vertices_.push_back(point.y);
    vertices_.push_back(point.z);
    UpdateMinMaxPoints(point);
    res = true;
  }
  return res;
}

bool s21::Model::ParsePolygons(std::istringstream& iss) {
  std::string polygon_str;
  bool polygon_start = true, res = true;
  int index, polygon_start_idx = 0;
  while (iss >> polygon_str && res) {
    std::istringstream polygon_iss(polygon_str);
    char tmp;
    polygon_iss >> index >> tmp;
    if (index < 0) {
      index += vertices_.size() + 1;
    }
    if (index <= 0 || static_cast<size_t>(index) > vertices_.size()) {
      res = false;
    } else {
      index--;  // To have an index, starting from 0
      if (polygon_start) {
        polygons_.push_back(index);
        polygon_start_idx = index;
        polygon_start = false;
      } else {
        polygons_edges_count_++;
        polygons_.insert(polygons_.end(), {index, index});
      }
    }
  }
  if (!polygon_start) {
    polygons_.push_back(polygon_start_idx);
    polygons_edges_count_++;
  }
  return res;
}

void s21::Model::UpdateMinMaxPoints(Vertex3d point) {
  min_point_.x = std::min(min_point_.x, point.x);
  min_point_.y = std::min(min_point_.y, point.y);
  min_point_.z = std::min(min_point_.z, point.z);
  max_point_.x = std::max(max_point_.x, point.x);
  max_point_.y = std::max(max_point_.y, point.y);
  max_point_.z = std::max(max_point_.z, point.z);
}

void s21::Model::TranslateToOrigin() {
  auto center_x = (max_point_.x + min_point_.x) / 2;
  auto center_y = (max_point_.y + min_point_.y) / 2;
  auto center_z = (max_point_.z + min_point_.z) / 2;
  auto size_coefficient = std::max({fabs(max_point_.x - min_point_.x),
                                    fabs(max_point_.y - min_point_.y),
                                    fabs(max_point_.z - min_point_.z)});
  if (size_coefficient != 0) size_coefficient = 2 / size_coefficient;

  for (size_t i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] = (vertices_[i] - center_x) * size_coefficient;
    vertices_[i + 1] = (vertices_[i + 1] - center_y) * size_coefficient;
    vertices_[i + 2] = (vertices_[i + 2] - center_z) * size_coefficient;
  }
}

void s21::Model::SaveVertices() { vertices_origin_ = vertices_; }
