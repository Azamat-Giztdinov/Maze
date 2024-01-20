#include "mazeview.h"

#include "ui_mazeview.h"

MazeView::MazeView(s21::MazeController *control, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MazeView) {
  ui_->setupUi(this);
  setFixedSize(size());
  maze_ = new s21::MazeGraphicsView(ui_->graphicsView, control);

  connect(ui_->buttonOpen, SIGNAL(clicked()), this, SLOT(openFileClicked()));
  connect(ui_->buttonSave, SIGNAL(clicked()), this, SLOT(saveFileClicked()));
  connect(ui_->buttonGenerate, SIGNAL(clicked()), this,
          SLOT(generateClicked()));
}

MazeView::~MazeView() { delete ui_; }

void MazeView::openFileClicked() {
  QString path = QFileDialog::getOpenFileName(this, "Select a file", "",
                                              "Maze file (*.txt)");
  maze_->openFile(path);
  ui_->spinBoxRows->setValue(maze_->getRows());
  ui_->spinBoxCols->setValue(maze_->getCols());
  if (!maze_->getCorrect()) {
    ShowMessage("Invalid file!");
  }
}

void MazeView::saveFileClicked() {
  if (!(maze_->getCorrect())) {
    ShowMessage("No maze!");
    return;
  }
  QString path = QFileDialog::getSaveFileName(this, "Select a file", "",
                                              "Maze file (*.txt)");
  maze_->saveFile(path);
}

void MazeView::generateClicked() {
  maze_->setWalls(ui_->spinBoxRows->value(), ui_->spinBoxCols->value());
}

void MazeView::ShowMessage(QString message) {
  QMessageBox messageBox;
  messageBox.setFixedSize(500, 200);
  messageBox.information(0, "Info", message);
}
