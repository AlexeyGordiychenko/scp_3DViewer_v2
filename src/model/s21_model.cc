#include "s21_model.h"

void s21::Model::ClearData() {
  vertices.clear();
  polygons.clear();
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
}

void s21::Model::UpdateMinMaxPoints(Vertex3d point) {
  if (point.x < min_point.x) min_point.x = point.x;
  if (point.y < min_point.y) min_point.y = point.y;
  if (point.z < min_point.z) min_point.z = point.z;
  if (point.x > max_point.x) max_point.x = point.x;
  if (point.y > max_point.y) max_point.y = point.y;
  if (point.z > max_point.z) max_point.z = point.z;
}

