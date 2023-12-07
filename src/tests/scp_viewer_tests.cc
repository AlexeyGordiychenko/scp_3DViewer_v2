#include "scp_viewer_tests.h"

#include <cmath>

#include "../model/scp_model.h"

TEST_F(ViewerTestCase, 0) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");
  EXPECT_TRUE(model.GetVertices() == kCubeVertices);
  EXPECT_TRUE(model.GetPolygons() == kCubePolygons);
}

TEST_F(ViewerTestCase, 1) {
  scp::Model model;
  EXPECT_THROW(model.ParseFile("tests/models/cube_wrong_vertice.txt"),
               std::runtime_error);
}

TEST_F(ViewerTestCase, 2) {
  scp::Model model;
  EXPECT_THROW(model.ParseFile("tests/models/cube_wrong_polygons.txt"),
               std::runtime_error);
}

TEST_F(ViewerTestCase, 3) {
  scp::Model model;
  model.ParseFile("tests/models/cube_negative_idx.txt");
  EXPECT_TRUE(model.GetVertices() == kCubeVertices);
  EXPECT_TRUE(model.GetPolygons() == kCubePolygons);
}

TEST_F(ViewerTestCase, 4) {
  scp::Model model;
  EXPECT_THROW(model.ParseFile("tests/models/file_not_found.txt"),
               std::runtime_error);
}

TEST_F(ViewerTestCase, 5) {
  scp::Model model;
  model.ParseFile("tests/models/flowers.txt");
  EXPECT_TRUE(model.GetVerticesCount() == 7608);
  EXPECT_TRUE(model.GetPolygonsEdgesCount() == 15747);
}

TEST_F(ViewerTestCase, 6) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");
  double ax = 1, ay = 1, az = 1;
  model.AffineMove(ax, ay, az);
  MoveVertices(kCubeVertices, ax, ay, az);
  EXPECT_TRUE(model.GetVertices() == kCubeVertices);
}

TEST_F(ViewerTestCase, 7) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");
  double ax = -5, ay = 8, az = 0;
  model.AffineMove(ax, ay, az);
  MoveVertices(kCubeVertices, ax, ay, az);
  EXPECT_TRUE(model.GetVertices() == kCubeVertices);
}

TEST_F(ViewerTestCase, 8) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");
  double ax = 0, ay = 0, az = 0;
  model.AffineMove(ax, ay, az);
  MoveVertices(kCubeVertices, ax, ay, az);
  EXPECT_TRUE(model.GetVertices() == kCubeVertices);
}

TEST_F(ViewerTestCase, 9) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");

  std::vector<double> result = {
      0.0, 0.0, 0.0, 0.0, -2.0, 0.0, 0.0, 0.0, 2.0, 0.0, -2.0, 2.0,
      2.0, 0.0, 0.0, 2.0, -2.0, 0.0, 2.0, 0.0, 2.0, 2.0, -2.0, 2.0,
  };

  model.AffineRotateX(M_PI / 2);
  auto vertices = model.GetVertices();

  EXPECT_EQ(result.size(), vertices.size());

  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_NEAR(result[i], vertices[i], kEps);
  }
}

TEST_F(ViewerTestCase, 10) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");

  std::vector<double> result = {
      0.0,  0.0, 0.0, 0.0,  0.0, -2.0, 0.0,  2.0, 0.0, 0.0,  2.0, -2.0,
      -2.0, 0.0, 0.0, -2.0, 0.0, -2.0, -2.0, 2.0, 0.0, -2.0, 2.0, -2.0,
  };

  model.AffineRotateY(M_PI);
  auto vertices = model.GetVertices();

  EXPECT_EQ(result.size(), vertices.size());

  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_NEAR(result[i], vertices[i], kEps);
  }
}

TEST_F(ViewerTestCase, 11) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");

  std::vector<double> result = {
      0.0,       0.0,       0.0, 0.0,       0.0,       2.0,
      -1.414214, -1.414214, 0.0, -1.414214, -1.414214, 2.0,
      -1.414214, 1.414214,  0.0, -1.414214, 1.414214,  2.0,
      -2.828428, 0.0,       0.0, -2.828428, 0.0,       2.0,
  };

  model.AffineRotateZ(3 * M_PI / 4);
  auto vertices = model.GetVertices();

  EXPECT_EQ(result.size(), vertices.size());

  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_NEAR(result[i], vertices[i], kEps);
  }
}

TEST_F(ViewerTestCase, 12) {
  scp::Model model;
  model.ParseFile("tests/models/cube.txt");

  std::vector<double> result = {
      0.0, 0.0, 0.0, 0.0, 0.0, 5, 0.0, 5, 0.0, 0.0, 5, 5,
      5,   0.0, 0.0, 5,   0.0, 5, 5,   5, 0.0, 5,   5, 5,
  };

  model.AffineScale(2.5);
  auto vertices = model.GetVertices();

  EXPECT_EQ(result.size(), vertices.size());

  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_NEAR(result[i], vertices[i], kEps);
  }
}

TEST_F(ViewerTestCase, 13) {
  scp::Model model;

  std::vector<double> result = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  model.Initialize("tests/models/cube_translate.txt");
  EXPECT_EQ(model.GetVertices(), result);
  model.AffineMove(1, 1, 1);
  model.RestoreVertices();
  EXPECT_EQ(model.GetVertices(), result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
