#include "s21_model.h"

void s21::Model::ClearData() {
  vertices.clear();
  polygons.clear();
  min_point = {0, 0, 0};
  max_point = {0, 0, 0};
}

void s21::Model::ParseFile(const std::string filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file.");
  }

  ClearData();

  std::string line;
  size_t line_num = 1;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string prefix;
    if (iss >> prefix) {
      if (prefix == "v") {
        Vertex3d point;
        if (iss >> point.x >> point.y >> point.z) {
          vertices.push_back(point);
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
            index += vertices.size() + 1;
          }
          if (index <= 0 || static_cast<size_t>(index) > vertices.size()) {
            throw std::runtime_error("Line: " + std::to_string(line_num) +
                                     " failed to read a facet.");
          } else {
            facet.push_back(index - 1);  // To have an index, starting from 0
          }
        }
        if (!facet.empty()) {
          polygons.push_back(facet);
        }
      }
    }
    ++line_num;
  }
  file.close();
  vertices_origin = vertices;
}

void s21::Model::UpdateMinMaxPoints(Vertex3d point) {
  if (point.x < min_point.x) min_point.x = point.x;
  if (point.y < min_point.y) min_point.y = point.y;
  if (point.z < min_point.z) min_point.z = point.z;
  if (point.x > max_point.x) max_point.x = point.x;
  if (point.y > max_point.y) max_point.y = point.y;
  if (point.z > max_point.z) max_point.z = point.z;
}

void s21::Model::SetDimentionalValues() {
  center_x = (max_point.x + min_point.x) / 2;
  center_y = (max_point.y + min_point.y) / 2;
  center_z = (max_point.z + min_point.z) / 2;
  double maxd = std::max({fabs(max_point.x - min_point.x),
                          fabs(max_point.y - min_point.y),
                          fabs(max_point.z - min_point.z)});
  if (maxd != 0) {
    size_coefficient = 2 / maxd;
  } else {
    size_coefficient = 0;
  }
}

void s21::Model::TranslateToFromOrigin(int k) {
  for (uint32_t i = 0; i < vertices.size(); i++) {
    vertices[i].x += k * center_x;
    vertices[i].y += k * center_y;
    vertices[i].z += k * center_z;
  }
}

void s21::Model::MoveCenter(double ax, double ay, double az) {
  center_x += ax;
  center_y += ay;
  center_z += az;
}

void s21::Model::RestoreVertices() { vertices = vertices_origin; }

void s21::Model::AffineMove(double ax, double ay, double az) {
  for (size_t i = 0; i < vertices.size(); i++) {
    vertices[i].x += ax;
    vertices[i].y += ay;
    vertices[i].z += az;
  }
}

void s21::Model::AffineRotateX(double angle) {
  if (angle) {
    double cos_angle = cos(angle), sin_angle = sin(angle);
    for (size_t i = 0; i < vertices.size(); i++) {
      double temp_y = vertices[i].y, temp_z = vertices[i].z;
      vertices[i].y = temp_y * cos_angle - temp_z * sin_angle;
      vertices[i].z = temp_y * sin_angle + temp_z * cos_angle;
    }
  }
}

void s21::Model::AffineRotateY(double angle) {
  if (angle) {
    double cos_angle = cos(angle), sin_angle = sin(angle);
    for (size_t i = 0; i < vertices.size(); i++) {
      double temp_x = vertices[i].x, temp_z = vertices[i].z;
      vertices[i].x = temp_x * cos_angle - temp_z * sin_angle;
      vertices[i].z = temp_x * sin_angle + temp_z * cos_angle;
    }
  }
}

void s21::Model::AffineRotateZ(double angle) {
  if (angle) {
    double cos_angle = cos(angle), sin_angle = sin(angle);
    for (size_t i = 0; i < vertices.size(); i++) {
      double temp_x = vertices[i].x, temp_y = vertices[i].y;
      vertices[i].x = temp_x * cos_angle - temp_y * sin_angle;
      vertices[i].y = temp_x * sin_angle + temp_y * cos_angle;
    }
  }
}

void s21::Model::AffineScale(double k) {
  if (k) {
    for (size_t i = 0; i < vertices.size(); i++) {
      vertices[i].x *= k;
      vertices[i].y *= k;
      vertices[i].z *= k;
    }
  }
}