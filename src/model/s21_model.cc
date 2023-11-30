#include "s21_model.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

void s21::Model::Initialize(const std::string filename) {
  is_empty_ = true;

  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file.");
  }

  ClearData();
  ParseFile(file);
  TranslateToOrigin();
  SaveVertices();

  is_empty_ = false;
}

void s21::Model::RestoreVertices() {
  vertices_ = vertices_origin_;
  center_x_ = 0;
  center_y_ = 0;
  center_z_ = 0;
}

void s21::Model::AffineMove(double ax, double ay, double az) {
  for (size_t i = 0; i < vertices_.size(); i++) {
    vertices_[i].x += ax;
    vertices_[i].y += ay;
    vertices_[i].z += az;
  }
  center_x_ += ax;
  center_y_ += ay;
  center_z_ += az;
}

void s21::Model::AffineRotateX(double angle) {
  if (angle) {
    double cos_angle = cos(angle), sin_angle = sin(angle);
    for (size_t i = 0; i < vertices_.size(); i++) {
      double temp_y = vertices_[i].y - center_y_,
             temp_z = vertices_[i].z - center_z_;
      vertices_[i].y = temp_y * cos_angle - temp_z * sin_angle + center_y_;
      vertices_[i].z = temp_y * sin_angle + temp_z * cos_angle + center_z_;
    }
  }
}

void s21::Model::AffineRotateY(double angle) {
  if (angle) {
    double cos_angle = cos(angle), sin_angle = sin(angle);
    for (size_t i = 0; i < vertices_.size(); i++) {
      double temp_x = vertices_[i].x - center_x_,
             temp_z = vertices_[i].z - center_z_;
      vertices_[i].x = temp_x * cos_angle - temp_z * sin_angle + center_x_;
      vertices_[i].z = temp_x * sin_angle + temp_z * cos_angle + center_z_;
    }
  }
}

void s21::Model::AffineRotateZ(double angle) {
  if (angle) {
    double cos_angle = cos(angle), sin_angle = sin(angle);
    for (size_t i = 0; i < vertices_.size(); i++) {
      double temp_x = vertices_[i].x - center_x_,
             temp_y = vertices_[i].y - center_y_;
      vertices_[i].x = temp_x * cos_angle - temp_y * sin_angle + center_x_;
      vertices_[i].y = temp_x * sin_angle + temp_y * cos_angle + center_y_;
    }
  }
}

void s21::Model::AffineScale(double k) {
  if (k) {
    for (size_t i = 0; i < vertices_.size(); i++) {
      vertices_[i].x *= k;
      vertices_[i].y *= k;
      vertices_[i].z *= k;
    }
  }
}

size_t s21::Model::GetPolygonsEdgesCount() const {
  size_t count = 0;
  for (auto polygon : polygons_) count += polygon.size();
  return count;
}

size_t s21::Model::GetVerticesCount() const { return vertices_.size(); }

const std::vector<std::vector<int>>& s21::Model::GetPolygons() const {
  return polygons_;
}

const std::vector<s21::Vertex3d>& s21::Model::GetVertices() const {
  return vertices_;
}

double s21::Model::GetCenterX() const { return center_x_; }
double s21::Model::GetCenterY() const { return center_y_; }
double s21::Model::GetCenterZ() const { return center_z_; }

bool s21::Model::Empty() const { return is_empty_; }

void s21::Model::ClearData() {
  vertices_.clear();
  polygons_.clear();
  min_point_ = {0, 0, 0};
  max_point_ = {0, 0, 0};
  center_x_ = 0, center_y_ = 0, center_z_ = 0;
}

void s21::Model::ParseFile(std::ifstream& file) {
  std::string line;
  size_t line_num = 1;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string prefix;
    if (iss >> prefix) {
      if (prefix == "v") {
        Vertex3d point;
        if (iss >> point.x >> point.y >> point.z) {
          vertices_.push_back(point);
          UpdateMinMaxPoints(point);
        } else {
          throw std::runtime_error("Line: " + std::to_string(line_num) +
                                   " failed to read a vertex.");
        }
      } else if (prefix == "f") {
        std::vector<int> facet;
        std::string facet_str;
        while (iss >> facet_str) {
          std::istringstream facet_iss(facet_str);
          int index;
          char tmp;
          facet_iss >> index >> tmp;
          if (index < 0) {
            index += vertices_.size() + 1;
          }
          if (index <= 0 || static_cast<size_t>(index) > vertices_.size()) {
            throw std::runtime_error("Line: " + std::to_string(line_num) +
                                     " failed to read a facet.");
          } else {
            facet.push_back(index - 1);  // To have an index, starting from 0
          }
        }
        if (!facet.empty()) {
          polygons_.push_back(facet);
        }
      }
    }
    ++line_num;
  }
  file.close();
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

  for (auto& vertex : vertices_) {
    vertex.x = (vertex.x - center_x) * size_coefficient;
    vertex.y = (vertex.y - center_y) * size_coefficient;
    vertex.z = (vertex.z - center_z) * size_coefficient;
  }
}

void s21::Model::SaveVertices() { vertices_origin_ = vertices_; }
