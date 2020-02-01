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
#include <stddef.h>
#include <stdbool.h>

class Player : public GameEntity
{
public:
    enum playern
    {
        PLAYER_ONE,
        PLAYER_TWO
    };

    Player(const playern player_n, const bool active);

    static void Init();

    void Update(GlobalData &gData) override;
    void Render(const Camera &camera) override;

private:
    const enum playern mId;
    Pad pad;
};

#endif /* PLAYER_H */
