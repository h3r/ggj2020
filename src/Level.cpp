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
	(void)data;
}

void Level::Render(const Camera& cam){
	for(uint8_t i=0; i<width; i++){
		for(uint8_t j=0; j<height; j++){
			tile_set.x = i * TILE_SIZE;
			tile_set.y = j * TILE_SIZE;
			cam.getPosition(tile_set.x, tile_set.y);

			//const uint8_t tile = tiles[i + j*tile_set_width_tiles];
			tile_set.u = tile_set_zero_u + 16;//(TILE_SIZE*tile)%tile_set_total_width;
			tile_set.v = tile_set_zero_v + 16;//(TILE_SIZE*tile)/tile_set_total_width;

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
	return GfxSpriteFromFile("DATA\\SPRITES\\tileset.TIM", &tile_set);
	tile_set_total_width = tile_set.w;
	tile_set_total_height = tile_set.h;
	tile_set_zero_u = tile_set.u;
	tile_set_zero_v = tile_set.v;

//	tile_set_width_tiles = tile_set_width / TILE_SIZE;
//	tile_set_height_tiles = tile_set_height / TILE_SIZE;
//	tile_set.w = tile_set.h = TILE_SIZE;
}

void Level::TestLevel(){
	width = MAX_LEVEL_SIZE_WIDTH;
	height = MAX_LEVEL_SIZE_HEIGHT;
	size = width * height;
	for(size_t i=0; i<size; i++){
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
