#include "GameEntity.hpp"

GameEntity::GameEntity(const bool active) :
    active(active)
{
}

bool GameEntity::isActive() const
{
    return active;
}
