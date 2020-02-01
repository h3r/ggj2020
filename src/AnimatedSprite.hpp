#pragma once

#include "Gfx.h"
#include "Camera.hpp"
#include <psxgpu.h>
#include <stdint.h>
#include <stdbool.h>

class AnimatedSprite;

typedef void (*animation_end_cb)(AnimatedSprite &ani, void* args);

struct animation_config
{
    short w, h;
    uint32_t nticks;
    bool loop;
    uint8_t start_frame, end_frame;
    animation_end_cb cb;
};

class AnimatedSprite
{
public:
    AnimatedSprite(const GsSprite &base_spr, const animation_config &c, void *args, const char *id);
    void Render(const Camera &cam);
    void SetPos(short x, short y);
    void Repeat();
    unsigned char GetSprAttribute();
    void SetSprAttribute(unsigned char attr);

private:
    const animation_config c;
    GsSprite spr;
    const short base_w;
    const short tpage_div;
    const uint8_t start_tpage;
    const short start_u, start_v;
    short x, y;
    uint16_t ticks_c;
    uint8_t frames_c;
    bool finished;
    void *const args;
    const char *const id;

    void PreRender();
};
