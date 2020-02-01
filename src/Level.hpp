
#pragma once

#include <psxgpu.h>
#include <stdint.h>

class GlobalData;
class Camera;

enum{
	MAX_LEVEL_SIZE_WIDTH = 32,
	MAX_LEVEL_SIZE_HEIGHT = 16,
	TILE_SIZE = 16,
	TILE_SET_WIDTH = 2,
	TILE_SET_HEIGHT = 2
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
	uint8_t width;
	uint8_t height;
	uint8_t tiles[MAX_LEVEL_SIZE_WIDTH*MAX_LEVEL_SIZE_HEIGHT];

	GsSprite tile_set;
};
