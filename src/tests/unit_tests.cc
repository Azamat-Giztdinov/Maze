#include <gtest/gtest.h>

#include <iostream>

#include "../model/mazemodel.h"

void expectVectorsEqual(const std::vector<std::pair<int, int>>& expected,
                        const std::vector<std::pair<int, int>>& actual) {
  ASSERT_EQ(expected.size(), actual.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].first, actual[i].first);
    EXPECT_EQ(expected[i].second, actual[i].second);
  }
}

TEST(Generation, Test_2) {
  MazeModel maze;
  maze.generateMaze(15, 13);
  EXPECT_EQ(maze.getRows(), 15);
  EXPECT_EQ(maze.getCols(), 13);
}

TEST(Path, Test_3) {
  MazeModel maze;
  maze.parseFile("./tests/maze1.txt");
  std::pair<int, int> start = {0, 0};
  std::pair<int, int> end = {3, 3};
  auto path = maze.findWay(start, end);
  std::vector<std::pair<int, int>> expected = {{3, 3}, {2, 3}, {1, 3}, {1, 2},
                                               {0, 2}, {0, 1}, {0, 0}};
  expectVectorsEqual(path, expected);
}

TEST(MazeSaverTest, GetSizeXTest) {
  MazeModel maze;
  maze.parseFile("./tests/maze2.txt");
  EXPECT_EQ(maze.getCols(), 3);
}

TEST(MazeSaverTest, GetSizeYTest) {
  MazeModel maze;
  maze.parseFile("./tests/maze2.txt");
  EXPECT_EQ(maze.getRows(), 3);
}

TEST(MazeSaverTest, SaveCurrentMazeTest) {
  MazeModel maze;
  maze.parseFile("./tests/maze2.txt");
  maze.saveFile("./tests/saveMaze.txt");
  std::ifstream file("./tests/saveMaze.txt");
  if (file.is_open()) {
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    EXPECT_EQ(lines[0], "3 3");
    EXPECT_EQ(lines[1], "1 0 1 ");
    EXPECT_EQ(lines[2], "0 1 0 ");
    EXPECT_EQ(lines[3], "1 1 1 ");
    EXPECT_EQ(lines[4], "");
    EXPECT_EQ(lines[5], "0 1 0 ");
    EXPECT_EQ(lines[6], "1 0 1 ");
    EXPECT_EQ(lines[7], "0 0 1 ");
  }
}

TEST(MazeSaverTest, FileOpenTest) {
  MazeModel maze;
  maze.parseFile("./tests/maze2.txt");
  maze.saveFile("./tests/saveMaze2.txt");
  std::ifstream file("./tests/saveMaze2.txt");
  EXPECT_TRUE(file.is_open());
  file.close();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
