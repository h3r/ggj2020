#pragma once

#include "Gfx.h"
#include <psxgpu.h>
#include <stdint.h>
#include <stdbool.h>

struct animation_coords
{
    short w, h;
    uint32_t nticks;
    bool loop;
};

class AnimatedSprite
{
public:
    AnimatedSprite(const char *fileName, const GsSprite &base_spr, const animation_coords &c);
    void update();

private:
    GsSprite spr;
    const animation_coords c;
    uint32_t counter;
    short orig_w, orig_h;
    short x_offset, y_offset;
};
