#pragma once

#include "Gfx.h"

class CompositeSpriteEntity
{
public:

    CompositeSpriteEntity(const GsSprite &spr) :
        mStartU(spr.u),
        mStartV(spr.v),
        mStartTPage(spr.tpage)
    {}

protected:

    void GetSpriteOrigin(unsigned char& startU,
                         unsigned char& startV,
                         unsigned char& startTpage) const;

private:

    const unsigned char mStartU, mStartV, mStartTPage;
};
