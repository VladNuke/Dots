#ifndef REFFEREE_H
#define REFFEREE_H

#include "GeneralHeader.h"

class PlayerData
{
public:
  explicit PlayerData(Player* player) : __score(0) { __player = player; }
  ~PlayerData();
  void set_start_min_max_positions(const size_t &row_count, const size_t &col_count);
  void set_new_min_max_position(const size_t &row, const size_t &col);
  void increment_score() { __score++; }
  size_t get_score() const { return __score; }
  // -
  Player* __player;
  QVector <size_t> min_row_pos;
  QVector <size_t> max_row_pos;
  QVector <size_t> min_col_pos;
  QVector <size_t> max_col_pos;
private:
  size_t __score;
  // - disable copy and assign -
  PlayerData (const PlayerData& ) {}
  PlayerData& operator=(PlayerData& ) { return *this; }

};

class Refferee
{
public:
  Refferee(QVector<PlayerData *> players_list, GameField *main_gamefield = 0);
  ~Refferee();
  // - getters -
  Player* get_active_player() const { return __players_list.at(__active_player)->__player; }
  GameField* get_main_gamefield() const { return __main_gamefield; }
  QVector <Dot*> get_updated_dots_list() const { return updated_dots; }
  // - setters -
  void set_active_player(const size_t& player_number);
  void set_main_gamefield(GameField *main_gamefield);
  void set_players_list(QVector<PlayerData *> players_list);
  // -
  void set_next_player();
  void make_move(const size_t& row, const size_t& col, bool &valid_turn, bool &extra_turn);
  bool check_success_move();
  void clear_all_players();

private:
  QVector <Dot*> updated_dots;
  QVector <PlayerData*> __players_list;
  size_t __active_player;
  GameField* __main_gamefield;
  // -
  void get_possibly_eaten_dots();
  void check_possibly_eaten_dots();
  // - disable copy and assign -
  Refferee (const Refferee& ) {}
  Refferee& operator=(Refferee& ) { return *this; }
};

#endif // REFFEREE_H

