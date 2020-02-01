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
#include "Gfx.h"

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
//	short x, y;
//	cam.getPosition(&x, &y);
//
//
//
//	uint8_t x_tile = x / TILE_SIZE;
//	uint8_t y_tile = y / TILE_SIZE;
//
//	uint8_t horizontal_tiles = 1 + X_SCREEN_RESOLUTION / TILE_SIZE;
//	uint8_t vertical_tiles = 1 + Y_SCREEN_RESOLUTION / TILE_SIZE;
//
//	for(uint8_t i=0; i<horizontal_tiles; i++){
//		for(uint8_t j=0; j<vertical_tiles; j++){
//
//		}
//	}
}

bool Level::Load(const char* file_name){
	/* File size in bytes. Modified by IOLoadFile(). */
    size_t e_size;
    size_t level_size = MAX_LEVEL_SIZE_X*MAX_LEVEL_SIZE_Y;

    /* Get buffer address where file data is contained. */
    const uint8_t *const buffer = IOLoadFile(file_name, &e_size);

    if(!buffer || e_size == IO_INVALID_FILE_SIZE || e_size != (level_size+2))
    	return false;

    width = buffer[0];
    height = buffer[1];

    for (size_t i=0; i<level_size; i++) {
    	if(buffer[i+2]<LEVEL_MAX_TILES) return false;
    	tiles[i] = buffer[i+2];
    }

    return true;
}

bool Level::LoadAssets(){
	return GfxSpriteFromFile("DATA\\SPRITES\\tileset.bmp", &tile_set);
}

void Level::TestLevel(){
	width = 16;
	height = 16;
	for(size_t i=0; i<width*height; i++){
		tiles[i] = i%2;
	}
}

void Level::GetDimensions(short& w, short& h) const{
	w = width * TILE_SIZE;
	h = height * TILE_SIZE;
}

/*******************************************************************//**
*
* \brief
*
************************************************************************/
