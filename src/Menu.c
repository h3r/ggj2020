/*******************************************************************//**
*
* \file     Menu.c
*
* \brief    Main menu handling.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Menu.h"
#include "Game.hpp"
#include "stdbool.h"
#include "Gfx.h"
#include <psxgpu.h>
#include <stdio.h>
#include <psx.h>

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

static GsSprite historySpr, menuSpr;

/* *************************************
 *  Local prototypes declaration
 * *************************************/

static bool MenuInit(void);
static enum tMenuResult MenuLoop(size_t* players);

/* *************************************
 * Functions definition
 * *************************************/

/*******************************************************************//**
*
* \brief    Reportedly, this function initializes the main menu.
*
************************************************************************/
static bool MenuInit(void)
{
    static bool init;

    if (!init)
    {
        init = true;
        GfxSpriteFromFile("\\DATA\\SPRITES\\START.TIM", &menuSpr);
        GfxSpriteFromFile("\\DATA\\SPRITES\\HISTORY.TIM", &historySpr);
    }

    return true;
}

/*******************************************************************//**
*
* \brief    Game logic entry point.
*
************************************************************************/
enum tMenuResult Menu(size_t* players)
{
    if (MenuInit())
    {
        return MenuLoop(players);
    }
    else
    {
        /* An error has happened while
         * initialising main menu. */
    }

    /* This result will be returned in case
     * menu initialization fails. */
    return MENU_RESULT_GAME_START;
}

static enum tMenuResult MenuLoop(size_t* players)
{
    {
        unsigned char lum = 0;
        unsigned short pads[2] = {0};
        bool exit = false;

        do
        {
            if (exit)
            {
                if (lum)
                    lum--;
            }
            else if (lum < NORMAL_LUMINANCE)
            {
                lum++;
            }
            else
            {
                PSX_ReadPad(&pads[0], &pads[1]);

                if (pads[0] || pads[1])
                {
                    exit = true;
                }
            }

            menuSpr.x = 0;
            menuSpr.w = X_SCREEN_RESOLUTION;
            menuSpr.h = Y_SCREEN_RESOLUTION;

            menuSpr.r =
            menuSpr.g =
            menuSpr.b = lum;

            GfxSortSprite(&menuSpr);

            GfxDrawScene();
        } while (lum);
    }

    unsigned short pads[2] = {0};

    {
        unsigned char lum = 0;
        static bool init;

        if (!init)
        {
            bool exit = false;
            init = true;

            do
            {
                if (exit)
                {
                    if (lum)
                        lum--;
                }
                else if (lum < NORMAL_LUMINANCE)
                {
                    lum++;
                }
                else
                {
                    PSX_ReadPad(&pads[0], &pads[1]);

                    if (pads[0] || pads[1])
                    {
                        exit = true;
                    }
                }

                historySpr.x = 0;
                historySpr.w = X_SCREEN_RESOLUTION;
                historySpr.h = Y_SCREEN_RESOLUTION;

                historySpr.r =
                historySpr.g =
                historySpr.b = lum;

                GfxSortSprite(&historySpr);

                GfxDrawScene();
            } while (lum);
        }
    }

    if ((pads[0] &= PAD_SQUARE)
            ||
        (pads[1] &= PAD_SQUARE))
    {
        *players = 2;
    }
    else
    {
        *players = 1;
    }

    return MENU_RESULT_GAME_START;
}

/*******************************************************************//**
*
* \brief    This function returns level selected by user.
*
* \return   \ref tLevel selected by user.
*
************************************************************************/
enum tLevel MenuGetSelectedLevel(void)
{
    return LEVEL_1;
}

size_t MenuGetSelectedPlayers(void)
{
    return 1;
}
