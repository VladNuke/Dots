#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTextCodec"

#include "GeneralHeader.h"
#include <QtGui>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  QTextCodec* codec;
  QGraphicsScene* main_scene;
  // - my -
  Refferee* main_ref;
  // - func -
  void SetStartParameters();
  void SetSignalsAndSlots();

private slots:
  void StartGame();
  void DrawTableField(GameField* field_data);
  void DrawDot(const int row, const int col);
};






#endif // MAINWINDOW_H
