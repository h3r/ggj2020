#include "GameEntity.hpp"

GameEntity::GameEntity(const bool active) :
    active(active)
{
}

bool GameEntity::isActive()
{
    return active;
}
