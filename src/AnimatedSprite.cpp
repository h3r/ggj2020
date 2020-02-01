#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "Gfx.h"
#include <psxgpu.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

AnimatedSprite::AnimatedSprite(const GsSprite &base_spr, const animation_config &c) :
    c(c),
    // Remember original width/height and texture page.
    base_w(base_spr.w),
    n_frames(c.end_frame - c.start_frame + 1),
    start_u(base_spr.u + ((c.start_frame * c.w) % base_w)),
    start_v(base_spr.v + (((c.start_frame * c.w) / base_w) * c.h)),
    x(0),
    y(0),
    ticks_c(0),
    frames_c(0),
    finished(false)
{
    // Sprite is already assumed to be loaded.
    if (!base_spr.w || !base_spr.h || !base_spr.tpage)
    {
        printf("No sprite has been loaded\n");
        return;
    }

    spr = base_spr;

    spr.w = c.w;
    spr.h = c.h;

    spr.u = start_u;
    spr.v = start_v;

    spr.w = c.w;
    spr.h = c.h;
}

void AnimatedSprite::Update()
{
    if (not finished)
    {
        if (++ticks_c >= c.nticks)
        {
            ticks_c = 0;

            const short new_u = (short)spr.u + spr.w;

            if (++frames_c >= n_frames)
            {
                if (c.loop)
                {
                    spr.u = start_u;
                    spr.v = start_v;
                    frames_c = 0;
                }
                else if (c.cb)
                {
                    printf("finished\n");
                    finished = true;
                    c.cb(*this);
                }
            }
            else if (new_u >= base_w + start_u)
            {
                spr.u = start_u;
                spr.v += spr.h;
            }
            else
            {
                spr.u = new_u;
            }
        }
    }
}

void AnimatedSprite::Render(const Camera &cam)
{
    spr.x = x;
    spr.y = y;

    GfxSortSprite(&spr);
}

void AnimatedSprite::SetPos(const short x, const short y)
{
    this->x = x;
    this->y = y;
}

void AnimatedSprite::Repeat()
{
    finished = false;
    spr.u = start_u;
    spr.v = start_v;
    frames_c = 0;
}
