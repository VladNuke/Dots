#ifndef PLAYER_H
#define PLAYER_H

#include "GeneralHeader.h"

class Player
{
public:
  Player(const QString& name, QIcon icon);
  ~Player();
  // - getters -
  QString get_name() const { return __name; }
  QIcon get_icon() const { return __icon; }
  // - setters -
  void set_name(const QString& name);
  void set_icon(QIcon icon);
  // -

private:
  QString __name;
  QIcon __icon;
  static int players_count;
  // - disable copy and assign -
  Player (const Player& ) {}
  Player& operator=(Player& ) { return *this; }
};

#endif // PLAYER_H
