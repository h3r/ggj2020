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
#include "Camera.hpp"
#include "IO.h"
#include "Gfx.h"

/* *************************************
 * Defines
 * *************************************/
enum{
	LEVEL_TILE_EMPTY,
	LEVEL_TILE_EMPTY_2,
	LEVEL_TILE_EMPTY_3,
	LEVEL_TILE_GROUND_FILL,
	LEVEL_TILE_GROUND_T,
	LEVEL_TILE_GROUND_T2,
	LEVEL_TILE_GROUND_T3,
	LEVEL_TILE_GROUND_T4,
	LEVEL_TILE_GROUND_TL,
	LEVEL_TILE_GROUND_TR,
	LEVEL_TILE_GROUND_BL,
	LEVEL_TILE_GROUND_BR,
	LEVEL_TILE_GROUND_B,
	LEVEL_TILE_GROUND_B2,
	LEVEL_TILE_GROUND_L,
	LEVEL_TILE_GROUND_R,


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
	(void)data;
}

void Level::Render(const Camera& cam){
	for(size_t i=0; i<width; i++){
		for(size_t j=0; j<height; j++){
			tile_set.x = i * TILE_SIZE;
			tile_set.y = j * TILE_SIZE;
			cam.getPosition(tile_set.x, tile_set.y);

			const uint8_t tile = tiles[i + j*width];
			tile_set.u = tile_set_zero_u + TILE_SIZE*(tile%tile_set_width_tiles);
			tile_set.v = tile_set_zero_v + TILE_SIZE*(tile/tile_set_width_tiles);

			GfxSortSprite(&tile_set);
		}
	}
}

bool Level::Load(const char* file_name){
	/* File size in bytes. Modified by IOLoadFile(). */
    size_t e_size;
    size_t level_size = MAX_LEVEL_SIZE_WIDTH*MAX_LEVEL_SIZE_HEIGHT;

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
	bool ret = GfxSpriteFromFile("DATA\\SPRITES\\tileset.TIM", &tile_set);
	tile_set_total_width = tile_set.w;
	tile_set_total_height = tile_set.h;
	tile_set_zero_u = tile_set.u;
	tile_set_zero_v = tile_set.v;

	tile_set_width_tiles = tile_set_total_width / TILE_SIZE;
//	tile_set_height_tiles = tile_set_total_height / TILE_SIZE;
	tile_set.w = tile_set.h = TILE_SIZE;
	return ret;
}

void Level::TestLevel(){
	width = MAX_LEVEL_SIZE_WIDTH;
	height = MAX_LEVEL_SIZE_HEIGHT;
	size = width * height;

	for(size_t j=0; j<height; j++){
		for(size_t i=0; i<width; i++){
			if(j == MAX_LEVEL_SIZE_HEIGHT-1) tiles[i+j*width] = LEVEL_TILE_GROUND_T;
			else tiles[i+j*width] = LEVEL_TILE_EMPTY;
		}
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
