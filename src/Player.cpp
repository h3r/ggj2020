/*******************************************************************//**
*
* \file     Player.c
*
* \author   Xavier Del Campo
*
* \brief    Implementation of Player module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Pad.hpp"
#include "Player.hpp"
#include "GlobalData.hpp"
#include "AnimatedSprite.hpp"
#include "Serial.h"
#include "Gfx.h"
#include "Sfx.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* *************************************
 * Defines
 * *************************************/

/* *************************************
 * Types definition
 * *************************************/

/* *************************************
 * Global variables definition
 * *************************************/

/* *************************************
 * Local variables definition
 * *************************************/

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/

static void jumping_finished(AnimatedSprite &ani, void *args)
{
    (void)ani;

    if (args)
    {
        Player &p = *(Player *)args;

        p.SetState(IDLE);
    }
}

static void rolling_finished(AnimatedSprite &ani, void *args)
{
    (void)ani;

    if (args)
    {
        Player &p = *(Player *)args;

        p.SetState(IDLE);
    }
}

// Static method
void Player::Init(GsSprite *const spr)
{
    static bool init;

    if (not init)
    {
        init = GfxSpriteFromFile("DATA\\SPRITES\\gatete.TIM", spr);
    }
}

void Player::SetState(const pl_state state)
{
    this->state = state;
}

Player::Player(const playern player_n, const bool active, const GsSprite &base_spr) :
    GameEntity(active),
    mId(player_n),
    pad(player_n),
    state(IDLE),
    prev_state(state),
    running(base_spr, animation_config{64, 64, 4, true, 16, 21, nullptr}, this),
    jumping(base_spr, animation_config{64, 64, 6, false, 0, 4, jumping_finished}, this),
    idle(base_spr, animation_config{64, 64, 12, true, 5, 7, nullptr}, this),
    rolling(base_spr, animation_config{64, 64, 6, false, 8, 15, rolling_finished}, this)
{
}

void Player::Update(GlobalData &gData)
{
    (void)gData;

    pad.handler();

    switch (state)
    {
        case IDLE:
            if (pad.singlePress(Pad::CROSS))
                state = JUMPING;
            else if (pad.singlePress(Pad::CIRCLE))
                state = ROLLING;
            break;

        default:
            break;
    }
}

void Player::Render(const Camera &camera)
{
    if (state != prev_state)
    {
        idle.Repeat();
        running.Repeat();
        rolling.Repeat();
        jumping.Repeat();
    }

    switch (state)
    {
        case IDLE:
            idle.Render(camera);
            break;

        case RUNNING:
            running.Render(camera);
            break;

        case ROLLING:
            rolling.Render(camera);
            break;

        case JUMPING:
            jumping.Render(camera);
            break;

        default:
            return;
    }

    prev_state = state;
}
