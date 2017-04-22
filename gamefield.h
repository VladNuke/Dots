#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "GeneralHeader.h"

class GameField
{
public:
  GameField();
  GameField(const int &row_count, const int &col_count);
  ~GameField();

  // - getters -
  size_t get_row_count() const { return __row_count; }
  size_t get_column_count() const { return __col_count; }
  Dot* get_dot(const size_t& row, const size_t& col) const { return __all_dots[row][col];}
  // - setters -
  void set_row_count(const size_t& row_count);
  void set_column_count(const size_t& col_count);
  // -
  bool set_dot(const size_t& row, const size_t& col, const size_t &owner);

private:
  size_t __row_count;
  size_t __col_count;
  QVector <QVector <Dot*> > __all_dots;
  // -
  void fill_all_field();
  bool check_dot_overlap(Dot* current_dot);
  bool check_dot_available(Dot* current_dot);
  bool check_dot_output(const size_t &row, const size_t &col);
  void clear_all_dots();

  static const size_t default_row_count;
  static const size_t default_col_count;
  static const size_t minimum_row_count;
  static const size_t minimum_col_count;
  static const size_t maximum_row_count;
  static const size_t maximum_col_count;
  // - disable copy and assign -
  GameField (const GameField& ) {}
  GameField& operator=(GameField& ) { return *this; }
};

#endif // GAMEFIELD_H
