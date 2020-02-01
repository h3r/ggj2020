/*******************************************************************//**
*
* \file     Level.cpp
*
* \brief    Implementation file for Level module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Level.hpp"
#include "IO.h"

/* *************************************
 * Defines
 * *************************************/
enum{
	LEVEL_TILE_EMPTY,
	LEVEL_TILE_GROUND,




	LEVEL_MAX_TILES
};

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
Level::Level() : width(0), height(0){

}

void Level::Update(GlobalData& data){

}

void Level::Render(const Camera& cam){

}

bool Level::load(const char* filename){
	/* File size in bytes. Modified by IOLoadFile(). */
    size_t eSize;
    size_t levelSize = MAX_LEVEL_SIZE_X*MAX_LEVEL_SIZE_Y;

    /* Get buffer address where file data is contained. */
    const uint8_t *const buffer = IOLoadFile(strFilePath, &eSize);

    if(!buffer || eSize == IO_INVALID_FILE_SIZE || eSize != (levelSize-2))
    	return false;

    width = buffer[0];
    height = buffer[1];

    for(int i=0; i<levelSize; i++){
    	if(buffer[i+2]<LEVEL_MAX_TILES) return false;
    	tiles[i] = buffer[i+2];
    }

    return true;
}


/*******************************************************************//**
*
* \brief
*
************************************************************************/
