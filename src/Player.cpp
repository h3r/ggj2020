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
#include "Vector2.hpp"


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
    GameEntity(active, PLAYER_SZ, PLAYER_SZ),
    mId(player_n),
    pad(player_n),
    state(IDLE),
    prev_state(state),
    dir(RIGHT),
    running(base_spr, animation_config{64, 64, 4, true, 16, 21, nullptr}, this),
    jumping(base_spr, animation_config{64, 64, 4, false, 0, 4, jumping_finished}, this),
    idle(base_spr, animation_config{64, 64, 8, true, 5, 7, nullptr}, this),
    rolling(base_spr, animation_config{64, 64, 4, false, 8, 15, rolling_finished}, this),
    falling(base_spr, animation_config{64, 64, 4, true, 3, 4, nullptr}, this),
    hp(7)
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

    GameEntity* collided_entity = gData.Players.collides(this, new_x, new_y);
    if (!collided_entity){
        x = new_x;
    }
    else
    {
        switch(collided_entity->type)
        {
            case TileType::DAMAGE:{
                int v = hp - 1;
                hp = (((0) > (v)) ? (0) : (v));
                hp = (((7) < (v)) ? (7) : (v));
                
                int ax = x,         ay = y;
                int bx = new_x ,    by = new_y;
                int ox = bx - ax,   oy = by - ay;

                if(!CreateCopy(x,y)){
                    Reset();
                    SetState(DEAD);
                    hp = 0;
                    break;
                }

                Push(-ox, -oy);

                break;
            }

            case TileType::PLAYER:{
                int ax = x,         ay = y;
                int bx = new_x ,    by = new_y;
                int ox = bx - ax,   oy = by - ay;

                Push(-ox, -oy + 1);

                break;
            }

            case TileType::PLAYER_COPY:{

                if(!collided_entity->isActive()) break;

                int v = hp + 1;
                hp = (((0) > (v)) ? (0) : (v));
                hp = (((7) < (v)) ? (7) : (v));

                int ax = x,         ay = y;
                int bx = new_x ,    by = new_y;
                int ox = bx - ax,   oy = by - ay;

                Push(-ox, -oy + 1);

                break;
            }

            default: break;

        }

    }
    
}

void Player::Push(int x, int y){
    x += x;
    y += y;
}

bool Player::CreateCopy(int x, int y){
    /*todo*/
    (void)x;
    (void)y;
    return true;
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

void Player::GetLastMovements(const short **const last_x_buf,
                              const short **const last_y_buf,
                              const GsSprite **const spr_buf) const
{
    *last_x_buf = last_x;
    *last_y_buf = last_y;
    *spr_buf = last_sprites;
}
