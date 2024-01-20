#include "mazemodel.h"

#include <iostream>

namespace s21 {
void MazeModel::parseFile(std::string filepath) {
  std::ifstream ifs(filepath);
  if (!(correct_ = ifs.is_open())) {
    return;
  }
  ifs >> this->rows_ >> this->cols_;
  if (rows_ < 1 || rows_ > 50 || cols_ < 1 || cols_ > 50) {
    correct_ = false;
    return;
  }
  right_walls_ = parseMatrix(ifs);
  ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  bottom_walls_ = parseMatrix(ifs);
  ifs.close();
}

void MazeModel::saveFile(const std::string& path) {
  std::ofstream ofs(path);
  if (!(correct_ = ofs.is_open())) {
    return;
  }
  ofs << rows_ << " " << cols_ << "\n";
  saveWall(ofs, right_walls_);
  ofs << "\n";
  saveWall(ofs, bottom_walls_);
  ofs.close();
}

void MazeModel::saveWall(std::ofstream& ofs, matrix& vect) {
  for (const auto& i : vect) {
    for (const int num : i) {
      ofs << num << " ";
    }
    ofs << "\n";
  }
}

MazeModel::matrix MazeModel::parseMatrix(std::ifstream& ifs) {
  matrix result(this->rows_, std::vector<int>(this->cols_, 0));
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      ifs >> result[i][j];
      if (result[i][j] != 0) {
        result[i][j] = 1;
      }
    }
  }
  return result;
}

void MazeModel::newMatrixSize() {
  matrix tmp(this->rows_, std::vector<int>(this->cols_, 0));
  right_walls_ = tmp;
  bottom_walls_ = tmp;
  matrix_maze_ = tmp;
}

void MazeModel::generateMaze(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  newMatrixSize();
  newValuesLine(0);
  generateMazeMatrix();
  correct_ = true;
}

void MazeModel::newValuesLine(int row) {
  for (int i = 0; i < cols_; ++i) {
    if (matrix_maze_[row][i] == 0) {
      matrix_maze_[row][i] = counter_++;
    }
  }
}

void MazeModel::generateMazeMatrix() {
  for (int i = 0; i < rows_; ++i) {
    generateRightWalls(i);
    generateBottomWalls(i);
    normalizeLine(i);
  }
}

void MazeModel::generateRightWalls(int row) {
  std::vector<int> random_line = generateRandoLine();
  for (int i = 0; i < cols_; ++i) {
    if (random_line[i] == 1) {
      right_walls_[row][i] = 1;
    } else {
      if (i != cols_ - 1) {
        if (matrix_maze_[row][i] == matrix_maze_[row][i + 1]) {
          right_walls_[row][i] = 1;
        } else {
          mergingLineFields(row, i);
        }
      }
    }
  }
}

void MazeModel::mergingLineFields(int row, int idx) {
  int num = matrix_maze_[row][idx + 1];
  for (int i = 0; i < cols_; ++i) {
    if (matrix_maze_[row][i] == num) {
      matrix_maze_[row][i] = matrix_maze_[row][idx];
    }
  }
}

void MazeModel::generateBottomWalls(int row) {
  std::vector<int> random_line = generateRandoLine();
  for (int i = 0; i < cols_; ++i) {
    if (random_line[i] != 0) {
      int num = matrix_maze_[row][i];
      int count_not_wall = 0;
      for (int j = 0; j < cols_; ++j) {
        if (matrix_maze_[row][j] == num && !bottom_walls_[row][j]) {
          ++count_not_wall;
        }
      }
      if (count_not_wall > 1) {
        bottom_walls_[row][i] = 1;
      }
    }
  }
}

std::vector<int> MazeModel::generateRandoLine() {
  std::vector<int> random_line;
  for (int i = 0; i < cols_; ++i) {
    random_line.push_back(rand() % 2);
  }
  return random_line;
}

void MazeModel::normalizeLine(int row) {
  if (row == rows_ - 1) {
    generateBottomLine();
  } else {
    matrix_maze_[row + 1] = matrix_maze_[row];
    for (int i = 0; i < cols_; ++i) {
      if (bottom_walls_[row][i] == 1) {
        matrix_maze_[row + 1][i] = 0;
      }
    }
    newValuesLine(row + 1);
  }
}

void MazeModel::generateBottomLine() {
  for (int i = 0; i < cols_; ++i) {
    bottom_walls_[rows_ - 1][i] = 1;
    if (i != cols_ - 1 &&
        matrix_maze_[rows_ - 1][i] != matrix_maze_[rows_ - 1][i + 1]) {
      right_walls_[rows_ - 1][i] = 0;
    }
  }
}

std::vector<std::pair<int, int>> MazeModel::findWay(std::pair<int, int> start,
                                                    std::pair<int, int> end) {
  counter_ = 1;
  matrix_maze_.clear();
  matrix_maze_.resize(rows_, std::vector<int>(cols_, 0));
  matrix_maze_[start.second][start.first] = counter_;

  while (matrix_maze_[end.second][end.first] == 0 &&
         (correct_ = pathCorrect())) {
    counter_++;
  }
  return pathMaze({end.second, end.first});
}

bool MazeModel::pathCorrect() {
  bool res = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_maze_[i][j] == counter_) {
        if (j > 0 && right_walls_[i][j - 1] == 0 && !matrix_maze_[i][j - 1]) {
          matrix_maze_[i][j - 1] = counter_ + 1;
        }
        if (i > 0 && bottom_walls_[i - 1][j] == 0 && !matrix_maze_[i - 1][j]) {
          matrix_maze_[i - 1][j] = counter_ + 1;
        }
        if (j < cols_ - 1 && right_walls_[i][j] == 0 &&
            !matrix_maze_[i][j + 1]) {
          matrix_maze_[i][j + 1] = counter_ + 1;
        }
        if (i < rows_ - 1 && bottom_walls_[i][j] == 0 &&
            !matrix_maze_[i + 1][j]) {
          matrix_maze_[i + 1][j] = counter_ + 1;
        }
        res = true;
      }
    }
  }
  return res;
}

std::vector<std::pair<int, int>> MazeModel::pathMaze(std::pair<int, int> pos) {
  std::vector<std::pair<int, int>> path;
  if (correct_) {
    path.push_back({pos.second, pos.first});
    while (counter_ > 1) {
      counter_--;
      if (pos.second > 0 &&
          matrix_maze_[pos.first][pos.second - 1] == counter_ &&
          right_walls_[pos.first][pos.second - 1] == 0) {
        --pos.second;
      }
      if (pos.first > 0 &&
          matrix_maze_[pos.first - 1][pos.second] == counter_ &&
          bottom_walls_[pos.first - 1][pos.second] == 0) {
        --pos.first;
      }
      if (pos.second < cols_ - 1 &&
          matrix_maze_[pos.first][pos.second + 1] == counter_ &&
          right_walls_[pos.first][pos.second] == 0) {
        ++pos.second;
      }
      if (pos.first < rows_ - 1 &&
          matrix_maze_[pos.first + 1][pos.second] == counter_ &&
          bottom_walls_[pos.first][pos.second] == 0) {
        ++pos.first;
      }
      path.push_back({pos.second, pos.first});
    }
  }
  return path;
}

}  // namespace s21