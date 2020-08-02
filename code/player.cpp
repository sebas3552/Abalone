#include "player.h"

Player::Player()
{

}

Player::Player(int id, Color color)
{
    this->id = id;
    this->color = color;
}

void Player::setId(int id)
{
    this->id = id;
}

void Player::setColor(Color color)
{
    this->color = color;
}

int Player::getId()
{
    return this->id;
}

Color Player::getColor()
{
    return this->color;
}
