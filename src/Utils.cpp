#include "Utils.hpp"
#include "psxgpu.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int rand_min_max(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

GsLine CreateLine(const struct vec2 begin, const struct vec2 end, unsigned char r, unsigned char g, unsigned char b, bool drawLine)
{
    GsLine line = {0, 0, 0, {0, 0}, {0, 0}, 0};
    // Init values
    line.r = r;
    line.g = g;
    line.b = b;
    line.attribute = ENABLE_TRANS | TRANS_MODE(0);

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

