#include "Camera.hpp"
#include "Math.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <psxgpu.h>

Camera::Camera() :
    mPosition(Vector2(0, 0))
{
    Default();
}

Camera::Camera(const Vector2& initialPos) :
    mPosition(initialPos)
{
    Default();
}

void Camera::Default()
{
    smoothing = true;
    smooth_value = 0.9;
    
    shake_elapsed = 0;
	shake_length = 0;
	shake_amount = 0;
}

void Camera::getPosition(short& x, short& y) const
{
    x += (X_SCREEN_RESOLUTION >> 1) - fix16_to_int(mPosition.X.value);
    y += (Y_SCREEN_RESOLUTION >> 1) - fix16_to_int(mPosition.Y.value);
}

void Camera::Update()
{
    // Follow always the player
    LookAt( Vector2(0, 0)/*  */ );

    if (shake_length > 0)
	{
		int shakeX = rand() * shake_amount * 2 - shake_amount;
		int shakeY = rand() * shake_amount * 2 - shake_amount;

		mPosition.X += shakeX;
		mPosition.Y += shakeY;

		shake_length--;
	}
}

void Camera::Shake(unsigned int amount, unsigned int length)
{
    // Assign shaking values
    shake_amount = amount;
	shake_length = length;
}

void Camera::LookAt(const Vector2& target, bool smooth)
{
	int gameMapSize = 0;//World::instance->map.width;

    // Poner esto fuera y poder cogerlo desde aquí
	int bufferX = 368;
    int bufferY = 240;

	int marginX = bufferX / 2;
    int marginY = bufferY / 2;

	int targetx = clamp(target.X.value, marginX, gameMapSize - marginX) - bufferX / 2;
	int targety = clamp(target.Y.value, marginY, gameMapSize - marginY) - bufferY / 2;

	mPosition.X = targetx;//smooth ? lerp(targetx, mPosition.X.value, smooth_value) : targetx;
	mPosition.Y = targety;//smooth ? lerp(targety, mPosition.Y.value, smooth_value) : targety;
}
