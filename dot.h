#ifndef DOT_H
#define DOT_H

#include "GeneralHeader.h"

enum dot_status { __free, __taken, __not_available, __in_progress_free, __in_progress_taken };

class Dot
{
public:
  Dot(const int& row, const int& col);
  Dot(const int& row, const int& col, const size_t& owner);
  ~Dot();
  // - getters -
  int get_row() const { return __row; }
  int get_column() const { return __col; }
  dot_status get_status() const { return __status; }
  size_t get_owner() const { return __owner_number; }
  // - setters -
  void set_row(const size_t& row) { __row = row; }
  void set_column(const size_t& col) { __col = col; }
  void set_status(dot_status status) { __status = status; }
  void set_owner(const size_t& owner = 0) { __owner_number = owner; }

private:
  int __row;
  int __col;
  size_t __owner_number;
  dot_status __status;
  // - disable copy and assign -
  Dot (const Dot& ) {}
  Dot& operator=(Dot& ) { return *this; }
};


#endif // DOT_H
