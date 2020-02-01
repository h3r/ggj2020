
#pragma once

#include <psxgpu.h>
#include <stdint.h>

class GlobalData;
class Camera;

enum{
	MAX_LEVEL_SIZE_WIDTH = 32,
	MAX_LEVEL_SIZE_HEIGHT = 16,
	TILE_SIZE = 16,
};

class Level{
public:
	Level();
	void Update(GlobalData& data);
	void Render(const Camera& cam);
	bool Load(const char* file_name);
	bool LoadAssets();
	void TestLevel();

	void GetDimensions(short& w, short& h) const;

private:
	unsigned short width;
	unsigned short height;
	unsigned short size;
	uint8_t tiles[MAX_LEVEL_SIZE_WIDTH*MAX_LEVEL_SIZE_HEIGHT];

	unsigned short tile_set_total_width;
	unsigned short tile_set_total_height;
	unsigned char tile_set_zero_u;
	unsigned char tile_set_zero_v;

	unsigned short tile_set_width_tiles;
	unsigned short tile_set_height_tiles;
	GsSprite tile_set;
};
