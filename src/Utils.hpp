
#pragma once

#include "psxgpu.h"

struct vec2{
    int x;
    int y;
};

GsLine CreateLine(const vec2 begin, const vec2 end, unsigned char r, unsigned char g, unsigned char b )
{
    GsLine line;
    line.r = r;
    line.g = g;
    line.b = b;

    line.x[0] = begin.x;
    line.x[1] = end.x;

    line.y[0] = begin.y;
    line.y[1] = end.y;

    return line;
}

void DrawLine(GsLine* line )
{
    GsSortLine(line);
}

