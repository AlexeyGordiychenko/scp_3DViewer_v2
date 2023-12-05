#ifndef S21_3DVIEWER_V2_TESTS_H
#define S21_3DVIEWER_V2_TESTS_H

#include <gtest/gtest.h>

class ViewerTestCase : public ::testing::Test {
 protected:
  double kEps = 1e-6;
  std::vector<double> kCubeVertices = {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2,
                                       2, 0, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2};
  std::vector<double> kCube1Vertices = {0, 0};
  std::vector<int> kCubePolygons = {
      0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0, 0, 1, 1, 3, 3, 0,
      2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0, 1, 5, 5, 7, 7, 1, 1, 7, 7, 3, 3, 1};

  void MoveVertices(std::vector<double>& vertices, double ax, double ay,
                    double az) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
      vertices[i] += ax;
      vertices[i + 1] += ay;
      vertices[i + 2] += az;
    }
  }
};

#endif  // S21_3DVIEWER_V2_TESTS_H
