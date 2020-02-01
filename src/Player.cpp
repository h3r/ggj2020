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

#define RUNNING_SPEED ((short)4)
#define JUMP_SPEED ((short)5)
#define ROLLING_SPEED ((short)3)

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
    dir(RIGHT),
    running(base_spr, animation_config{64, 64, 4, true, false, 16, 21, nullptr}, this),
    jumping(base_spr, animation_config{64, 64, 4, false, false, 0, 4, jumping_finished}, this),
    idle(base_spr, animation_config{64, 64, 8, true, true, 5, 7, nullptr}, this),
    rolling(base_spr, animation_config{64, 64, 4, false, false, 8, 15, rolling_finished}, this),
    falling(base_spr, animation_config{64, 64, 4, true, false, 3, 4, nullptr}, this)
{
}

void Player::Update(GlobalData &gData)
{
    const short gravity = 2;

    short new_x = x;
    short new_y = y + gravity;
    pad.handler();

    switch (state)
    {
        case RUNNING:
            if (pad.released(Pad::LEFT) || pad.released(Pad::RIGHT))
                state = IDLE;
            // Fall through.
        case IDLE:
            if (pad.singlePress(Pad::CROSS))
                state = JUMPING;
            else if (pad.singlePress(Pad::CIRCLE))
                state = ROLLING;
            else if (pad.keyPressed(Pad::LEFT))
            {
                new_x -= RUNNING_SPEED;
                state = RUNNING;
                dir = LEFT;
            }
            else if (pad.keyPressed(Pad::RIGHT))
            {
                new_x += RUNNING_SPEED;
                state = RUNNING;
                dir = RIGHT;
            }

            break;

        case JUMPING:
        {
            const short speed = dir == RIGHT ? JUMP_SPEED : -JUMP_SPEED;
            new_x += speed;
        }
            break;

        case ROLLING:
        {
            const short speed = dir == RIGHT ? ROLLING_SPEED : -ROLLING_SPEED;
            new_x += speed;
        }
            break;

        default:
            break;
    }

    if (!gData.Players.collides(this, new_x, new_y))
        x = new_x;
}

void Player::Render(const Camera &camera)
{
    AnimatedSprite *ani;

    switch (state)
    {
        case IDLE:
            ani = &idle;
            break;

        case RUNNING:
            ani = &running;
            break;

        case ROLLING:
            ani = &rolling;
            break;

        case JUMPING:
            ani = &jumping;
            break;

        default:
            return;
    }

    if (state != prev_state)
    {
        ani->Repeat();
    }

    switch (dir)
    {
        case LEFT:
            ani->SetSprAttribute(ani->GetSprAttribute() | H_FLIP);
            break;

        case RIGHT:
            ani->SetSprAttribute(ani->GetSprAttribute() & ~H_FLIP);
            break;
    }

    ani->SetPos(x, y);
    ani->Render(camera);

    prev_state = state;
}
