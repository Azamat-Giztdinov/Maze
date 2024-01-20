#include <QApplication>

#include "mazeview.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("Maze");
  s21::MazeModel *model = new s21::MazeModel;
  s21::MazeController *controller = new s21::MazeController(model);
  MazeView *view = new MazeView(controller);
  view->show();
  return app.exec();
}
