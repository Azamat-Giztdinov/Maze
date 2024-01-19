#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <memory>

#include "mazegraphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeView;
}
QT_END_NAMESPACE

class MazeView : public QMainWindow {
  Q_OBJECT

 public:
  MazeView(MazeController *control, QWidget *parent = nullptr);
  ~MazeView();

 private slots:
  void openFileClicked();
  void saveFileClicked();
  void generateClicked();
  void ShowMessage(QString message);

 private:
  Ui::MazeView *ui_;
  MazeGraphicsView *maze_;
};

#endif  // MAZEVIEW_H
