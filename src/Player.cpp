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

static const box jumping_box[] =
{
    {4, 38, 52, 26},
    {2, 26, 53, 26},
    {3, 17, 53, 21},
    {6, 32, 53, 19},
    {2, 42, 53, 22}
};

static const box idle_box[] =
{
    {19, 22, 38, 43},
    {14, 24, 42, 39},
    {5, 24, 51, 39}
};

static const box rolling_box[] =
{
    {4, 39, 53, 25},
    {15, 41, 33, 22},
    {25, 43, 21, 21},
    {20, 42, 20, 22},
    {22, 36, 27, 26},
    {19, 31, 33, 33},
    {9, 35, 50, 24},
    {4, 42, 54, 20}
};

static const box running_box[] =
{
    {1, 47, 53, 20},
    {8, 44, 53, 18},
    {5, 42, 52, 22},
    {7, 44, 52, 18},
    {3, 38, 54, 26},
    {3, 38, 53, 26}
};

Player::Player(const playern player_n, const bool active, const GsSprite &base_spr) :
    GameEntity(active),
    mId(player_n),
    pad(player_n),
    state(IDLE),
    prev_state(state),
    dir(RIGHT),
    running(base_spr, animation_config{PLAYER_SZ, PLAYER_SZ, 4, true, 16, 21, nullptr}, running_box, this),
    jumping(base_spr, animation_config{PLAYER_SZ, PLAYER_SZ, 4, false, 0, 4, jumping_finished}, jumping_box, this),
    idle(base_spr, animation_config{PLAYER_SZ, PLAYER_SZ, 8, true, 5, 7, nullptr}, idle_box, this),
    rolling(base_spr, animation_config{PLAYER_SZ, PLAYER_SZ, 4, false, 8, 15, rolling_finished}, rolling_box, this),
    falling(base_spr, animation_config{PLAYER_SZ, PLAYER_SZ, 4, true, 3, 4, nullptr}, nullptr, this),
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

void Player::getPos(short &x, short &y) const
{
    x = this->x + b.x;
    y = this->y + b.y;
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

    b.x = x;
    b.y = y;
    b.w = w;
    b.h = h;

    ani->getBox(b, dir == LEFT);

    static GsRectangle r;

    r.x = x + b.x;
    r.y = y + b.y;
    r.w = b.w;
    r.h = b.h;
    r.r = r.g = r.b = 0xFF;
    r.attribute = ENABLE_TRANS | TRANS_MODE(0);

    ani->SetPos(x, y);
    w = PLAYER_SZ;
    h = PLAYER_SZ;
    ani->Render(camera);

    GsSortRectangle(&r);

    w = b.w;
    h = b.h;

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
