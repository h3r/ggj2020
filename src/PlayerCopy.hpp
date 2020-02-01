#pragma once

#include "GameEntity.hpp"
#include "Player.hpp"
#include "GlobalData.hpp"
#include "Camera.hpp"

class PlayerCopy : public GameEntity
{
public:
    explicit PlayerCopy(const Player &pl);
    void Update(GlobalData &gData) override;
    void Render(const Camera &cam) override;

private:
    const Player &pl;
    GsSprite spr;
    unsigned int spawn_timer;
};
