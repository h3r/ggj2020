
#pragma once

#include <stdint.h>

class GlobalData;
class Camera;

#define MAX_LEVEL_SIZE_X 16
#define MAX_LEVEL_SIZE_Y 16

class Level{
public:
	Level();
	void Update(GlobalData& data);
	void Render(const Camera& cam);
	bool load(const char* filename);

private:
	uint8_t width;
	uint8_t height;
	uint8_t tiles[MAX_LEVEL_SIZE_X*MAX_LEVEL_SIZE_Y];
};
