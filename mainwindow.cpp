#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dot.h"
#include "gamefield.h"
#include "player.h"
#include "refferee.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  // --- Кодек для текста ---
  codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);
  // ---
  main_scene = 0;
  main_ref = 0;
  // ---
  SetStartParameters();
  SetSignalsAndSlots();
}

MainWindow::~MainWindow()
{
  if (main_ref != 0) delete main_ref;
  if (main_scene != 0) delete main_scene;
  delete ui;
}

// ===== FUNCTIONS =====

void MainWindow::SetSignalsAndSlots()
{
  connect(ui->pushButton_start, SIGNAL(clicked()), SLOT(StartGame()));
  connect(ui->tableWidget_field, SIGNAL(cellClicked(int,int)), SLOT(DrawDot(int,int)));
}

void MainWindow::SetStartParameters()
{

}


// ===== SLOTS =====

void MainWindow::StartGame()
{
  PlayerData* p1 = new PlayerData(new Player(ui->lineEdit_player1->text(), QIcon(QPixmap(":/images/png/resources/cat.png"))));
  //QIcon(QPixmap(":/Buttons/icons/tick_48.png")),"Сохранить");
  PlayerData* p2 = new PlayerData(new Player(ui->lineEdit_player2->text(), QIcon(QPixmap(":/images/png/resources/dog.png"))));
  QVector<PlayerData*> v;
  v.push_back(p1);
  v.push_back(p2);
  GameField* f = new GameField(ui->spinBox_width->value(), ui->spinBox_height->value());
  main_ref = new Refferee(v,f);
  DrawTableField(f);
}

void MainWindow::DrawTableField(GameField *field_data)
{
  const int rows = field_data->get_row_count();
  const int cols = field_data->get_column_count();
  const int row_height = ui->tableWidget_field->height()/rows;
  const int col_width = ui->tableWidget_field->width()/cols;
  ui->tableWidget_field->setRowCount(rows);
  ui->tableWidget_field->setColumnCount(cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      QTableWidgetItem* temp = new QTableWidgetItem();
      ui->tableWidget_field->setItem(i, j, temp);
      if (i == 0)
      {
        ui->tableWidget_field->setColumnWidth(j, col_width);
      }
    }
    ui->tableWidget_field->setRowHeight(i, row_height);
  }
  ui->tableWidget_field->setIconSize(QSize(col_width, row_height));

}

void MainWindow::DrawDot(const int row, const int col)
{
  Player* cur_player = main_ref->get_active_player();
  bool valid_turn = false;
  bool extra_turn = false;
  main_ref->make_move(row, col, valid_turn, extra_turn);
  if ( valid_turn )
  {
    ui->tableWidget_field->item(row, col)->setIcon(cur_player->get_icon());
    QString log_report;
    if ( extra_turn )
    {
      foreach(Dot* d, main_ref->get_updated_dots_list())
      {
        ui->tableWidget_field->item(d->get_row(), d->get_column())->setIcon(QIcon(QPixmap(":/images/png/resources/disabled.png")));
      }
      log_report = cur_player->get_name() + " поставил точку в (" + QString::number(row) + "," + QString::number(col) + ").\nПолучает дополнительный ход ";
    }
    else
    {
      main_ref->set_next_player();
      log_report = cur_player->get_name() + " поставил точку в (" + QString::number(row) + "," + QString::number(col) + ").\nХодит " + main_ref->get_active_player()->get_name();
    }
    ui->textEdit_report->setText(log_report);
  }
}
