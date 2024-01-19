#include "mazegraphicsview.h"

MazeGraphicsView::MazeGraphicsView(QGraphicsView* qgraph,
                                   MazeController* controll)
    : QGraphicsView(qgraph), controller_(controll) {
  scene_ = new QGraphicsScene(0, 0, 500, 500, this);
  setScene(scene_);
  paintMaze();
}

void MazeGraphicsView::saveFile(const QString& path) {
  if (rows_ && cols_) {
    controller_->saveFile(path.toStdString());
  }
}

void MazeGraphicsView::setWalls(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  controller_->generateMaze(rows_, cols_);
  writeWalls();
  paintMaze();
}

void MazeGraphicsView::openFile(QString path) {
  controller_->openFile(path.toStdString());
  if (controller_->getCorrect()) {
    writeWalls();
    paintMaze();
  }
}

void MazeGraphicsView::writeWalls() {
  right_walls_.clear();
  bottom_walls_.clear();
  rows_ = controller_->getRows();
  cols_ = controller_->getCols();
  right_walls_ = controller_->getRightWalls();
  bottom_walls_ = controller_->getBottomWalls();
}

void MazeGraphicsView::clear() {
  clearPath();
  scene_->clear();
}

void MazeGraphicsView::clearPath() {
  for (int i = 0; i < path_poins_.size(); ++i) {
    delete path_poins_[i];
    path_poins_[i] = nullptr;
  }
  path_poins_.clear();
  for (int i = 0; i < path_lines_.size(); ++i) {
    delete path_lines_[i];
    path_lines_[i] = nullptr;
  }
  path_lines_.clear();
  points_start_and_end.clear();
}

void MazeGraphicsView::paintMaze() {
  clear();
  if (!controller_->getCorrect()) {
    return;
  }
  float size_h = (sceneRect().width()) * 1.0 / cols_;
  float size_v = (sceneRect().height()) * 1.0 / rows_;
  int wallThickness = 2;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (size_t(i) < right_walls_.size() &&
          size_t(j) < right_walls_[i].size() - 1 && right_walls_[i][j] == 1) {
        QGraphicsRectItem* wall =
            new QGraphicsRectItem((j + 1) * size_h - wallThickness, i * size_v,
                                  wallThickness, size_v);
        wall->setPen(QPen(Qt::white));
        scene_->addItem(wall);
      }
      if (size_t(i) < bottom_walls_.size() - 1 &&
          size_t(j) < bottom_walls_[i].size() && bottom_walls_[i][j] == 1) {
        QGraphicsRectItem* wall =
            new QGraphicsRectItem(j * size_h, (i + 1) * size_v - wallThickness,
                                  size_h, wallThickness);
        wall->setPen(QPen(Qt::white));
        scene_->addItem(wall);
      }
    }
  }
}

void MazeGraphicsView::mousePressEvent(QMouseEvent* mouse) {
  if (!controller_->getCols() || !controller_->getRows()) {
    return;
  }
  if (path_poins_.size() == 2) {
    clearPath();
  }
  QPointF clickPoint = mapToScene(mouse->pos());
  size_h_ = (sceneRect().width()) / cols_;
  size_v_ = (sceneRect().height()) / rows_;
  clickPoint.setX(int(clickPoint.x() / size_h_) * size_h_ + size_h_ / 4);
  clickPoint.setY(int(clickPoint.y() / size_v_) * size_v_ + size_v_ / 4);
  QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(
      clickPoint.x(), clickPoint.y(), size_h_ / 2, size_v_ / 2);
  ellipse->setPen(QPen(Qt::white));
  points_start_and_end.append(clickPoint);
  path_poins_.append(ellipse);
  scene_->addItem(ellipse);
  printWay();
}

void MazeGraphicsView::printWay() {
  if (path_poins_.size() != 2) {
    return;
  }
  auto start = points_start_and_end[0];
  auto end = points_start_and_end[1];
  auto path = findWay({start.x() / size_h_, start.y() / size_v_},
                      {end.x() / size_h_, end.y() / size_v_});
  for (int i = 0; i < int(path.size()) - 1; ++i) {
    auto point_one_ = path[i];
    auto point_two_ = path[i + 1];
    QGraphicsLineItem* line =
        new QGraphicsLineItem(point_one_.first * size_h_ + size_h_ / 2,
                              point_one_.second * size_v_ + size_v_ / 2,
                              point_two_.first * size_h_ + size_h_ / 2,
                              point_two_.second * size_v_ + size_v_ / 2);
    line->setPen(QPen(Qt::green));
    path_lines_.append(line);
    scene_->addItem(line);
  }
}
