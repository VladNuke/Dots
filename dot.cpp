#include "dot.h"

Dot::Dot(const int &row, const int &col) : __owner_number(0), __status(__free)
{
  //qDebug()<<"Dot::constructor";
  set_row(row);
  set_column(col);
}

Dot::Dot(const int &row, const int &col, const size_t &owner) : __status(__taken)
{
  //qDebug()<<"Dot::constructor";
  set_row(row);
  set_column(col);
  set_owner(owner);
}

Dot::~Dot()
{
  //qDebug()<<"Dot::destructor";
}

