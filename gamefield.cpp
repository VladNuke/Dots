#include "gamefield.h"

#include "dot.h"

const size_t GameField::default_row_count = 50;
const size_t GameField::default_col_count = 50;
const size_t GameField::minimum_row_count = 10;
const size_t GameField::minimum_col_count = 10;
const size_t GameField::maximum_row_count = 100;
const size_t GameField::maximum_col_count = 100;

GameField::GameField()
{
  qDebug()<<"GameField::constructor";
  set_row_count(GameField::default_row_count);
  set_column_count(GameField::default_col_count);
  fill_all_field();
}

GameField::GameField(const int &row_count, const int &col_count)
{
  qDebug()<<"GameField::constructor";
  set_row_count(row_count);
  set_column_count(col_count);
  fill_all_field();
}

GameField::~GameField()
{
  qDebug()<<"GameField::destructor";
  clear_all_dots();
}

// === setters ===
void GameField::set_row_count(const size_t &row_count)
{
  if ( row_count < GameField::minimum_row_count || row_count > GameField::maximum_row_count )
  {
    QMessageBox::warning(0,"Внимание!","Введена некорректная ширина поля. Установлена ширина по умолчанию (" +QString::number(GameField::default_row_count)+ ")." );
    __row_count = GameField::default_row_count;
  }
  else
    __row_count = row_count;
}

void GameField::set_column_count(const size_t &col_count)
{
  if ( col_count < GameField::minimum_col_count || col_count > GameField::maximum_col_count )
  {
    QMessageBox::warning(0,"Внимание!","Введена некорректная высота поля. Установлена высота по умолчанию (" +QString::number(GameField::default_col_count)+ ")." );
    __col_count = GameField::default_col_count;
  }
  else
    __col_count = col_count;
}

// === fill all field with new dots on start ===
void GameField::fill_all_field()
{
  Dot* temp_dot;
  QVector<Dot*> horz_array;
  for (size_t i = 0; i < __row_count; i++)
  {
    horz_array.clear();
    for (size_t j = 0; j < __col_count; j++)
    {
      temp_dot = new Dot(i, j);
      horz_array.push_back(temp_dot);
    }
    __all_dots.push_back(horz_array);
  }
}

// === create new dot ===
bool GameField::set_dot(const size_t &row, const size_t &col, const size_t &owner)
{
  bool result = true;
  qDebug()<<"GameField::set_dot";
  if ( !check_dot_output(row, col) )
  {
    QMessageBox::warning(0, "Внимание!", "Координаты точки выходят за пределы игрового поля. Выберите другую точку.");
    result = false;
    return result;
  }
  Dot* d = __all_dots[row][col];
  if ( !check_dot_overlap(d) )
  {
    QMessageBox::warning(0, "Внимание!", "В указанном месте уже установлена точка. Выберите другую точку.");
    result = false;
  }
  else if ( !check_dot_available(d) )
  {
    QMessageBox::warning(0, "Внимание!", "Указанное место расположено внутри занятой области. Выберите другую точку.");
    result = false;
  }
  else
  {
    d->set_owner(owner);
    d->set_status(__taken);
    result = true;
  }
  return result;
}

// === check dot coordinates for output from game field ===
bool GameField::check_dot_output(const size_t &row, const size_t &col)
{
  bool result = true;
  if (row >= __row_count || col >= __col_count)
  {
    result = false;
  }
  return result;
}

// === check dot coordinates if field already have the dot here ===
bool GameField::check_dot_overlap(Dot *current_dot)
{
  bool result = true;
  if (current_dot->get_owner() != 0 && current_dot->get_status() == __taken)
  {
    result = false;
  }
  return result;
}

// === check dot coordinates if dot is not available (in closed area) ===
bool GameField::check_dot_available(Dot *current_dot)
{
  bool result = true;
  if (current_dot->get_status() == __not_available)
  {
    result = false;
  }
  return result;
}

// === delete all dots from field ===
void GameField::clear_all_dots()
{
  if (__all_dots.size() > 0)
  {
    foreach(QVector<Dot*> v, __all_dots)
    {
      foreach (Dot* d, v)
      { delete d; }
      v.clear();
    }
    __all_dots.clear();
  }
}

