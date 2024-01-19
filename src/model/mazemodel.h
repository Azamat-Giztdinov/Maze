#ifndef A1_MAZE_SRC_MODEL_MAZEMODEL_H_
#define A1_MAZE_SRC_MODEL_MAZEMODEL_H_

#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <vector>

class MazeModel {
 public:
  using matrix = std::vector<std::vector<int>>;

  MazeModel() = default;
  ~MazeModel() = default;
  void parseFile(std::string filepath);
  void saveFile(const std::string& path);
  void saveWall(std::ofstream& ofs, matrix& vect);
  matrix& getRightWalls() { return right_walls_; }
  matrix& getBottomWalls() { return bottom_walls_; }
  int getRows() { return rows_; }
  int getCols() { return cols_; }
  bool getCorrect() { return correct_; }
  void generateMaze(int rows, int cols);
  bool pathCorrect();
  std::vector<std::pair<int, int>> findWay(std::pair<int, int> start,
                                           std::pair<int, int> end);
  std::vector<std::pair<int, int>> pathMaze(std::pair<int, int> end);

 private:
  int rows_ = 0;
  int cols_ = 0;
  matrix right_walls_{};
  matrix bottom_walls_{};
  matrix matrix_maze_{};
  bool correct_ = false;
  int counter_{1};

  matrix parseMatrix(std::ifstream& ifs);
  void newMatrixSize();
  void newValuesLine(int row);
  void generateMazeMatrix();
  void generateRightWalls(int row);
  void generateBottomWalls(int row);
  std::vector<int> generateRandoLine();
  void normalizeLine(int row);
  void generateBottomLine();
  void mergingLineFields(int row, int idx);
};

#endif  // A1_MAZE_SRC_MODEL_MAZEMODEL_H_
