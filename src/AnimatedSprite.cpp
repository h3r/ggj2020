#include "AnimatedSprite.hpp"
#include <psxgpu.h>
#include <stdint.h>
#include <stdio.h>

AnimatedSprite::AnimatedSprite(const char *fileName, const GsSprite &base_spr, const animation_coords &c) :
    c(c),
    counter(0)
{
    // Sprite is already assumed to be loaded.
    if (!base_spr.w || !base_spr.h || !base_spr.tpage)
    {
        printf("No sprite has been loaded\n");
        return;
    }

    // Remember original width/height.
    orig_w = spr.w;
    orig_h = spr.h;

    spr.w = c.w;
    spr.h = c.h;

    x_offset = spr.u;
    y_offset = spr.v;
}

void AnimatedSprite::update()
{
    if (++counter >= c.nticks)
    {

        counter = 0;
    }
}
