#include <QApplication>

#include "mazeview.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("Maze");
  MazeModel *model = new MazeModel;
  MazeController *controller = new MazeController(model);
  MazeView *view = new MazeView(controller);
  view->show();
  return app.exec();
}
