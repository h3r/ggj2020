
#pragma once

#include "psxgpu.h"
#include <string.h>

struct vec2{
    int x;
    int y;
};

GsLine CreateLine(const vec2 begin, const vec2 end, unsigned char r, unsigned char g, unsigned char b, bool drawLine = false )
{
    GsLine line;
    // Init values
    memset(&line, 0, sizeof line);

    line.r = r;
    line.g = g;
    line.b = b;

    line.x[0] = begin.x;
    line.x[1] = end.x;

    line.y[0] = begin.y;
    line.y[1] = end.y;

    if(drawLine)
        GsSortLine(&line);

    return line;
}

void DrawLine(GsLine* line)
{
    GsSortLine(line);
}

