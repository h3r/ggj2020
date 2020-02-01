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
#include "GlobalData.h"
#include <stddef.h>
#include <stdbool.h>

class Player
{
public:
    enum playern
    {
        PLAYER_ONE,
        PLAYER_TWO
    };

    Player(const playern player_n, const bool active);
    
    static void Init();

    void Update(GlobalData &gData);
    void Render(const Camera &camera);
    bool isActive();

private:
    const enum playern mId;
    Pad pad;
    bool active;

};

#endif /* PLAYER_H */
