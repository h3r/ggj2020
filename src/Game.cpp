/***************************************************************************//**
*
* \file     Game.cpp
*
* \brief    Game main module and entry point for game logic.
*
*******************************************************************************/

/* *****************************************************************************
 * Includes
 * ****************************************************************************/

#include "GlobalData.h"
#include "Game.hpp"
#include "Gfx.h"
#include "Menu.h"
#include "Level.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include "Camera.hpp"
#include "Serial.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* *****************************************************************************
 * Defines
 * ***************************************************************************e*/

/* *****************************************************************************
 * Types definition
 * ****************************************************************************/

/* *****************************************************************************
 * Global variables definition
 * ****************************************************************************/

/* *****************************************************************************
 * Local variables definition
 * ****************************************************************************/

static Level level;

static GsSprite playerSpr;
static GsSprite test_sprite;

/* *****************************************************************************
 * Local prototypes declaration
 * ****************************************************************************/

static void GameStart(const size_t players);
static void GameInit(const size_t players);
static void GameInitFiles(void);
static void GameLoop(const size_t players);

/* *****************************************************************************
 * Functions definition
 * ****************************************************************************/

/***************************************************************************//**
*
* \brief    Game logic entry point.
*
*******************************************************************************/
void Game(void)
{
    /* Execute game main menu and determine
     * next steps depending on its result. */
    size_t players;

    switch (Menu(&players))
    {
        case MENU_RESULT_GAME_START:
            /* Start gameplay given number of players. */
            GameStart(players);
            break;

        case MENU_RESULT_UNDEFINED:
            /* Fall through. */
        default:
            /* Invalid result. Restart game. */
            break;
    }
}

/***************************************************************************//**
*
* \brief    Initializes a level indicated by eSelectedLevel and
*           all game structures.
*
* \param    players
*               Number of active players.
*
*******************************************************************************/
static void GameStart(const size_t players)
{
    /* Game initialization. */
    GameInit(players);

    /* Gameplay. */
    GameLoop(players);
}

/***************************************************************************//**
*
* \brief    Initializes basic elements.
*
* \param    players
*               Number of active players.
*
*******************************************************************************/
static void GameInit(const size_t players)
{
    static bool initDone;

    if (!initDone)
    {
        /* Load needed files. */
        GameInitFiles();

        /* Set first game initialization flag. */
        initDone = true;
    }
}

static void GameInitFiles(void)
{
    Player::Init();
    GfxSpriteFromFile("DATA\\SPRITES\\test.TIM", &test_sprite);
}

static void GameLoop(const size_t players)
{
    Camera cam;

    // Players
    Player player_array[2] =
    {
        {Player::PLAYER_ONE, players > Player::PLAYER_ONE},
        {Player::PLAYER_TWO, players > Player::PLAYER_TWO}
    };

    ArrayManager<Player> pl(ARRAY_SIZE(player_array), player_array);

    GlobalData data =
    {
        // ArrayManager<Player>& Players;
        pl,
        // Camera &cam;
        cam
    };

    test_sprite.x = (X_SCREEN_RESOLUTION >> 1) - 32;
    test_sprite.y = (Y_SCREEN_RESOLUTION >> 1) - 32;

    while (GfxIsBusy())
        ;

    for (;;)
    {
        // Game logic
        pl.update(data);

        // Rendering
        while (GfxIsBusy())
            ;

        GfxClear();

        GfxSortSprite(&test_sprite);

        pl.render(cam);
        GfxDrawScene();
    }
}
