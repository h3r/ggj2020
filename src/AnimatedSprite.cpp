#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "Gfx.h"
#include <psxgpu.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

AnimatedSprite::AnimatedSprite(const GsSprite &base_spr, const animation_config &c, const box *const b, void *const args) :
    c(c),
    spr(base_spr),
    // Remember original width/height and texture page.
    base_w(base_spr.w),
    tpage_div(COLORMODE(base_spr.attribute) == COLORMODE_16BPP ?
                GFX_TPAGE_WIDTH
             :COLORMODE(base_spr.attribute) == COLORMODE_8BPP ?
                GFX_TPAGE_WIDTH << 1
             :COLORMODE(base_spr.attribute) == COLORMODE_4BPP ?
                GFX_TPAGE_WIDTH << 2: 1),
    start_tpage(base_spr.u + ((c.start_frame * c.w) % base_w) < MAX_SIZE_FOR_GSSPRITE ?
                    base_spr.tpage
                :   base_spr.tpage + (base_spr.u + (c.start_frame * c.w) / tpage_div)),
    start_u(base_spr.u + ((c.start_frame * c.w) % base_w) < MAX_SIZE_FOR_GSSPRITE ?
            base_spr.u + ((c.start_frame * c.w) % base_w)
            :(c.start_frame * c.w) % tpage_div),
    start_v(base_spr.v + (((c.start_frame * c.w) / base_w) * c.h)),
    x(0),
    y(0),
    ticks_c(0),
    frames_c(0),
    finished(false),
    args(args),
    b(b)
{
    // Sprite is already assumed to be loaded.
    if (!base_spr.w || !base_spr.h || !base_spr.tpage)
    {
        printf("No sprite has been loaded\n");
        return;
    }

    spr.w = c.w;
    spr.h = c.h;

    spr.u = start_u;
    spr.v = start_v;
    spr.tpage = start_tpage;

    spr.w = c.w;
    spr.h = c.h;
}

void AnimatedSprite::PreRender()
{
    if (not finished)
    {
        if (++ticks_c >= c.nticks)
        {
            ticks_c = 0;

            const short new_u = (short)spr.u + spr.w;
            const uint8_t n_frames = c.end_frame - c.start_frame + 1;

            if (++frames_c >= n_frames)
            {
                frames_c = 0;

                if (c.loop)
                {
                    spr.u = start_u;
                    spr.v = start_v;
                    spr.tpage = start_tpage;
                }
                else if (c.cb)
                {
                    finished = true;
                    c.cb(*this, args);
                }
            }
            else if (new_u >= base_w + start_u)
            {
                spr.u = start_u;
                spr.v += spr.h;
                spr.tpage = start_tpage;
            }
            else if (new_u >= MAX_SIZE_FOR_GSSPRITE)
            {
                uint8_t tpage_inc;

                switch (COLORMODE(spr.attribute))
                {
                    case COLORMODE_16BPP:
                        tpage_inc = MAX_SIZE_FOR_GSSPRITE >> GFX_TPAGE_WIDTH_BITSHIFT;
                        break;

                    case COLORMODE_8BPP:
                        tpage_inc = MAX_SIZE_FOR_GSSPRITE >> (GFX_TPAGE_WIDTH_BITSHIFT + 1);
                        break;

                    case COLORMODE_4BPP:
                        tpage_inc = MAX_SIZE_FOR_GSSPRITE >> (GFX_TPAGE_WIDTH_BITSHIFT + 2);
                        break;
                }

                spr.u = 0;
                spr.tpage += tpage_inc;
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
    PreRender();

    spr.x = x;
    spr.y = y;

    cam.getPosition(spr.x,spr.y);

    GfxSortSprite(&spr);
}

void AnimatedSprite::getBox(box &b, const bool mirror)
{
    if (this->b)
    {
        const size_t i = frames_c;

        if (mirror)
        {
            const short mirror_x = spr.w - this->b[i].w - this->b[i].x;

            const box ab =
            {
                mirror_x,
                this->b[i].y,
                this->b[i].w,
                this->b[i].h
            };

            b = ab;
        }
        else
            b = this->b[i];
    }
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
    spr.tpage = start_tpage;
    ticks_c = 0;
    frames_c = 0;
}

unsigned char AnimatedSprite::GetSprAttribute()
{
    return spr.attribute;
}

void AnimatedSprite::SetSprAttribute(const unsigned char attr)
{
    spr.attribute = attr;
}
