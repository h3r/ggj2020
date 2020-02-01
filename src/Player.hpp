#ifndef PLAYER_H
#define PLAYER_H

/*******************************************************************//**
*
* \file     Player.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Player module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Pad.hpp"
#include "Gfx.h"
#include "ArrayManager.hpp"
#include "GameEntity.hpp"
#include "GlobalData.hpp"
#include "AnimatedSprite.hpp"
#include <stddef.h>
#include <stdbool.h>
#include <psxgpu.h>

enum pl_state
{
    IDLE,
    RUNNING,
    JUMPING,
    FALLING,
    ROLLING,
    DEAD,
};

enum pl_direction
{
    LEFT,
    RIGHT
};

class Player : public GameEntity
{
    
public:
    enum playern
    {
        PLAYER_ONE,
        PLAYER_TWO
    };

    Player(const playern player_n, const bool active, const GsSprite &base_spr);

    static void Init(GsSprite *spr);

    void Update(GlobalData &gData) override;
    void Render(const Camera &camera) override;

    void SetState(pl_state state);
    void Hit(unsigned int hp_loss);
    void Push(int x, int y);
    bool CreateCopy(int x, int y);
    void Reset(){/*todo*/}

private:
    const enum playern mId;
    Pad pad;
    pl_state state, prev_state;
    pl_direction dir;
    AnimatedSprite running, jumping, idle, rolling, falling;
    unsigned int hp;
};

#endif /* PLAYER_H */
