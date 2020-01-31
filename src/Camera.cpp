#include "Camera.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <psxgpu.h>

Camera::Camera() :
    mPosition(Vector2(0, 0))
{
}

/* 1 player tracking. */
void Camera::Update(const Vector2& p1)
{
    mPosition = p1;
}

/* 2 player tracking. */
void Camera::Update(const Vector2& p1, const Vector2& p2)
{
    mPosition.X.value = abs(p1.X.value - p2.X.value) / 2;
    mPosition.Y.value = abs(p1.Y.value - p2.Y.value) / 2;

    if (p1.X.value <= p2.X.value)
    {
        mPosition.X.value = p1.X.value + mPosition.X.value;
    }
    else
    {
        mPosition.X.value = p2.X.value + mPosition.X.value;
    }

    if (p1.Y.value <= p2.Y.value)
    {
        mPosition.Y.value = p1.Y.value + mPosition.Y.value;
    }
    else
    {
        mPosition.Y.value = p2.Y.value + mPosition.Y.value;
    }
}

void Camera::getPosition(short& x, short& y) const
{
    x += (X_SCREEN_RESOLUTION >> 1) - fix16_to_int(mPosition.X.value);
    y += (Y_SCREEN_RESOLUTION >> 1) - fix16_to_int(mPosition.Y.value);
}
