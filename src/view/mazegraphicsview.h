#ifndef MAZEGRAPHICSVIEW_H
#define MAZEGRAPHICSVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <vector>

#include "../controller/mazecontroller.h"

namespace s21 {

class MazeGraphicsView : public QGraphicsView {
 public:
  using matrix = std::vector<std::vector<int>>;
  MazeGraphicsView(QGraphicsView *qgraph, MazeController *controll);
  void setWalls(int rows, int cols);
  void openFile(QString path);
  void paintMaze();
  void saveFile(const QString &path);
  bool getCorrect() { return controller_->getCorrect(); }
  int getRows() { return rows_; };
  int getCols() { return cols_; };

 private slots:
  void writeWalls();
  void mousePressEvent(QMouseEvent *mouse) override;
  void clear();
  void clearPath();
  void printWay();
  std::vector<std::pair<int, int>> findWay(std::pair<int, int> start,
                                           std::pair<int, int> end) {
    return controller_->findWay(start, end);
  }

 private:
  QGraphicsScene *scene_;
  int rows_ = 0;
  int cols_ = 0;
  matrix right_walls_{};
  matrix bottom_walls_{};
  float size_h_ = 0;
  float size_v_ = 0;

  MazeController *controller_;
  QVector<QGraphicsEllipseItem *> path_poins_;
  QVector<QPointF> points_start_and_end;
  QVector<QGraphicsLineItem *> path_lines_;
};

}  // namespace s21

#endif  // MAZEGRAPHICSVIEW_H
