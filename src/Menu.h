#ifndef MENU_H
#define MENU_H

/*******************************************************************//**
*
* \file     Menu.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Menu module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Game.hpp"
#include <stddef.h>
#include <psxgpu.h>

/* *************************************
 * Defines
 * *************************************/

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* *************************************
 * Public types definition
 * *************************************/

EXTERNC enum tMenuResult
{
    MENU_RESULT_UNDEFINED,
    MENU_RESULT_EDITOR,
    MENU_RESULT_GAME_START
};

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

EXTERNC enum tMenuResult Menu(size_t* players);
EXTERNC enum tLevel MenuGetSelectedLevel(void);
EXTERNC size_t MenuGetSelectedPlayers(void);

#endif /* MENU_H */
