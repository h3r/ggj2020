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
#include "GlobalData.h"
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

static GsSprite heartSpr;
static SsVag chargeSnd;

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/

void PlayerInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\HEART.TIM", &heartSpr);
    SfxUploadSound("DATA\\SOUNDS\\CHARGE.VAG", &chargeSnd);
}

Player::Player(const playern player_n, const bool active, GsSprite &spr, GsSprite &sprRes) :
    mId(player_n),
    pad(player_n),
    active(active)
{
}

bool Player::isActive()
{
    return active;
}

void Player::Update(GlobalData &gData)
{
    pad.handler();
}

void Player::render(const Camera &camera)
{
}
