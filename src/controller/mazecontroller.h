#ifndef A1_MAZE_SRC_CONTROLLER_MAZECONTROLLER_H_
#define A1_MAZE_SRC_CONTROLLER_MAZECONTROLLER_H_

#include "../model/mazemodel.h"

namespace s21 {

class MazeController {
 public:
  using matrix = std::vector<std::vector<int>>;
  MazeController(MazeModel* model) : model_(model){};
  void openFile(const std::string& path) { model_->parseFile(path); };
  void saveFile(const std::string& path) { model_->saveFile(path); }
  matrix& getRightWalls() { return model_->getRightWalls(); }
  matrix& getBottomWalls() { return model_->getBottomWalls(); }
  int getRows() { return model_->getRows(); }
  int getCols() { return model_->getCols(); }
  bool getCorrect() { return model_->getCorrect(); }
  void generateMaze(int rows, int cols) { model_->generateMaze(rows, cols); }
  std::vector<std::pair<int, int>> findWay(std::pair<int, int> start,
                                           std::pair<int, int> end) {
    return model_->findWay(start, end);
  }

 private:
  MazeModel* model_;
};

}  // namespace s21

#endif  // A1_MAZE_SRC_CONTROLLER_MAZECONTROLLER_H_
