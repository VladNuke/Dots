#include "player.h"

int Player::players_count = 0;

Player::Player(const QString &name, QIcon icon)
{
  qDebug()<<"Player::constructor";
  Player::players_count ++;
  set_name(name);
  set_icon(icon);

}

Player::~Player()
{
  qDebug()<<"Player::destructor";
  Player::players_count --;
}

// === setters ===

void Player::set_name(const QString &name)
{
  if ( name.isEmpty() || name.length() >= 20)
  {
    __name = "Игрок_" + QString::number(Player::players_count);
    QMessageBox::warning(0,"Внимание!","Введено некорректное имя. Установлено имя по умолчанию (" +__name+ ")." );
  }
  else
    __name = name;
}

void Player::set_icon(QIcon icon)
{
  __icon = icon;
}

// ===

