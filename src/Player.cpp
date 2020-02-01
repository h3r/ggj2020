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


// Static method
void Player::Init()
{
}

Player::Player(const playern player_n, const bool active) :
    GameEntity(active),
    mId(player_n),
    pad(player_n)
{
}

void Player::Update(GlobalData &gData)
{
    (void)gData;
    pad.handler();
}

void Player::Render(const Camera &camera)
{
    (void)camera;
}
