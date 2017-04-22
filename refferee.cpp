#include "refferee.h"
#include "gamefield.h"
#include "player.h"
#include "dot.h"

Refferee::Refferee(QVector<PlayerData *> players_list, GameField* main_gamefield)
{
  qDebug()<<"Refferee::constructor";
  set_main_gamefield(main_gamefield);
  set_players_list(players_list);
}

Refferee::~Refferee()
{
  qDebug()<<"Refferee::destructor";
  if (__main_gamefield != 0)
  {
    delete __main_gamefield;
  }
  clear_all_players();
}

// === setters ===
void Refferee::set_main_gamefield(GameField *main_gamefield)
{
  if (main_gamefield == 0)
  {
    __main_gamefield = new GameField();
  }
  else
  {
    __main_gamefield = main_gamefield;
  }

}

void Refferee::set_players_list(QVector<PlayerData *> players_list)
{
  if (players_list.size() == 0)
  {
    QMessageBox::warning(0,"Внимание!","Список игроков пуст, добавляем игрока...");
    PlayerData* temp_data = new PlayerData(new Player("Игрок_1", QIcon(QPixmap(":/images/png/resources/default.png"))));
    __players_list.push_back(temp_data);
  }
  else
  {
    __players_list = players_list;
  }
  foreach(PlayerData* p, __players_list) { p->set_start_min_max_positions(__main_gamefield->get_row_count(), __main_gamefield->get_column_count()); }
  set_active_player(0);
}

void Refferee::set_active_player(const size_t &player_number)
{
  if (__players_list.size() == 0)
  {
    QMessageBox::warning(0,"Внимание!","Список игроков пуст, необходимо установить количество игроков.");
    return;
  }
  if (player_number >= __players_list.size())
  {
    __active_player = 0;
  }
  else
  {
    __active_player = player_number;
  }
}



// ===

void Refferee::set_next_player()
{
  size_t i = __active_player + 1;
  set_active_player(i);
}

void Refferee::make_move(const size_t &row, const size_t &col, bool& valid_turn, bool& extra_turn)
{
  size_t owner_number = __active_player + 1;
  if ( !__main_gamefield->set_dot(row, col, owner_number) )
  {
    valid_turn = false;
    return; // - try to put dot in incorrect place
  }
  else
  {
    valid_turn = true;
    __players_list.at(__active_player)->set_new_min_max_position(row, col);
    extra_turn = check_success_move();
  }
}

// === проверка, был ли ход удачным ("съедены" точки противника) ===
bool Refferee::check_success_move()
{
  //qDebug()<<"Refferee::check_success_move";
  updated_dots.clear();
  // - get dots -
  //qDebug()<<"start dots total: "<<updated_dots.size();
  get_possibly_eaten_dots();
  qDebug()<<"possible dots total: "<<updated_dots.size();
  if ( updated_dots.isEmpty() )
  {
    return false; // - no dots updated, next player turn
  }
  // - check dots -
  check_possibly_eaten_dots();
  if ( updated_dots.isEmpty() )
  {
    return false; // - all dots weren't updated, next player turn
  }
  // - all remaining dots are 'eaten'
  bool enemy_dots_eaten = false;
  foreach(Dot* d, updated_dots)
  {
    d->set_status(__not_available);
    if (d->get_owner() != 0)
    {
      __players_list.at(__active_player)->increment_score();
      enemy_dots_eaten = true; // - if there were enemy dots, player gets extra turn -
    }
    d->set_owner(__active_player+1);
  }
  return enemy_dots_eaten;
}

// --- add all posibly updated dots into vector ---
void Refferee::get_possibly_eaten_dots()
{
  //qDebug()<<"Refferee::get_possibly_eaten_dots";
  size_t col_count = __main_gamefield->get_column_count();
  size_t row_count = __main_gamefield->get_row_count();
  for (size_t i = 0; i < row_count; i++)
  {
    for(size_t j = 0; j < col_count; j++)
    {
      if (j > __players_list.at(__active_player)->min_col_pos[i] && j < __players_list.at(__active_player)->max_col_pos[i]
          && i > __players_list.at(__active_player)->min_row_pos[j] && i < __players_list.at(__active_player)->max_row_pos[j])
      {
        Dot* d = __main_gamefield->get_dot(i, j);
        // - add only empty or enemy dots -
        if ( d->get_status() == __free )
        {
          d->set_status(__in_progress_free);
          updated_dots.push_back(d);
        }
        else if ( d->get_status() == __taken && d->get_owner() != (__active_player+1) )
        {
          d->set_status(__in_progress_taken);
          updated_dots.push_back(d);
        }
      }
    }
  }
  //qDebug()<<"~Refferee::get_possibly_eaten_dots";
}

// --- check all posibly updated dots ---
void Refferee::check_possibly_eaten_dots()
{
  qDebug()<<"Refferee::check_possibly_eaten_dots";
  foreach(Dot* d, updated_dots)
  {
    qDebug()<<"possible dot: row="<<d->get_row()<<" col="<<d->get_column();
  }

  bool all_dots_checked = false;
  int count = 0;
  while( !all_dots_checked )
  {
    qDebug()<<"iteration: "<<count<<"items count = "<<updated_dots.size(); count++;
    size_t dot_counter = updated_dots.size();
    all_dots_checked = true;
    for(size_t i = 0; i < dot_counter; i++)
    {
      Dot* d = updated_dots.at(i);

      int temp_row = d->get_row(), temp_col = d->get_column();
      Dot* upper = __main_gamefield->get_dot(temp_row-1, temp_col);
      Dot* lower = __main_gamefield->get_dot(temp_row+1, temp_col);
      Dot* right = __main_gamefield->get_dot(temp_row, temp_col+1);
      Dot* left = __main_gamefield->get_dot(temp_row, temp_col-1);
qDebug()<<"neighbour status: "<<upper->get_status()<<lower->get_status()<<right->get_status()<<left->get_status();
qDebug()<<"neighbour owner: "<<upper->get_owner()<<lower->get_owner()<<right->get_owner()<<left->get_owner();
      if (upper->get_status() == __free || (upper->get_status() == __taken && upper->get_owner() != (__active_player+1))
          || lower->get_status() == __free || (lower->get_status() == __taken && lower->get_owner() != (__active_player+1))
          || right->get_status() == __free || (right->get_status() == __taken && right->get_owner() != (__active_player+1))
          || left->get_status() == __free || (left->get_status() == __taken && left->get_owner() != (__active_player+1)))
      {
qDebug()<<"free dot: row="<<temp_row<<" col="<<temp_col;
        if (d->get_status() == __in_progress_free) { d->set_status(__free); } // - restore initial status -
        else if (d->get_status() == __in_progress_taken) { d->set_status(__taken); }
        updated_dots.remove(i);
        all_dots_checked = false;
        break;
      }
    }
    qDebug()<<"all_dots checked="<<all_dots_checked;
  }
  //qDebug()<<"~Refferee::check_possibly_eaten_dots";
}

// - delete all player data -
void Refferee::clear_all_players()
{
  qDebug()<<"clear all players";
  if (__players_list.size() > 0)
  {
    foreach(PlayerData* p, __players_list)
      delete p;
    __players_list.clear();
  }
}


// ============================
// ===== class PlayerData =====
// ============================

PlayerData::~PlayerData()
{
  if(__player != 0) { delete __player; }
}

// === set start minimal and max dot indexes ===
void PlayerData::set_start_min_max_positions(const size_t& row_count, const size_t& col_count)
{
  for (size_t i = 0; i < row_count; i++)
  {
    min_row_pos.push_back(row_count);
    max_row_pos.push_back(0);
  }

  for (size_t i = 0; i < col_count; i++)
  {
    min_col_pos.push_back(col_count);
    max_col_pos.push_back(0);
  }
}

void PlayerData::set_new_min_max_position(const size_t &row, const size_t &col)
{
  if (row < min_row_pos[col]) { min_row_pos[col] = row; }
  if (row > max_row_pos[col]) { max_row_pos[col] = row; }
  if (col < min_col_pos[row]) { min_col_pos[row] = col; }
  if (col > max_col_pos[row]) { max_col_pos[row] = col; }
  //qDebug()<<min_x_pos[y_pos]<<max_x_pos[y_pos]<<min_y_pos[x_pos]<<max_y_pos[x_pos];
}

