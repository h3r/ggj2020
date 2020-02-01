#include "GameEntity.hpp"

GameEntity::GameEntity(const bool active) :
    active(active),
    x(0),
    y(0)
{
}

bool GameEntity::isActive() const
{
    return active;
}

void GameEntity::getPos(short &x, short &y) const
{
    x = this->x;
    y = this->y;
}

void GameEntity::setPos(const short x, const short y)
{
    this->x = x;
    this->y = y;
}
