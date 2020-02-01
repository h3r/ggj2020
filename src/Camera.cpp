#include "Camera.hpp"
#include "Math.hpp"
#include "Level.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <psxgpu.h>

Camera::Camera() :
    X(X_SCREEN_RESOLUTION/2),
    Y(Y_SCREEN_RESOLUTION/2)
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
    x += ((X_SCREEN_RESOLUTION >> 1) - 32) - X;
    y += (Y_SCREEN_RESOLUTION - 64) - Y; // Camera is not centered in Y
}

void Camera::Update(const int x, const int y, const Level& level)
{
    printf("Cat: [%d,%d] | Cam: [%d,%d]\n", x,y, X,Y);
    LookAt( x, y, level );

    if (shake_length > 0)
	{
		/* int shakeX = rand() * shake_amount * 2 - shake_amount;
		int shakeY = rand() * shake_amount * 2 - shake_amount; */

		//X += 10;
        //Y += 10;
		//Y += shakeY;

		//shake_length--;
	}
}

void Camera::Shake(unsigned int amount, unsigned int length)
{
    // Assign shaking values
    shake_amount = amount;
	shake_length = length;
}

void Camera::LookAt(const int x, const int y, const Level& level, bool smooth)
{
    (void)level;
    (void)smooth;

    int Tx = x;
    int Ty = y;

	/* short mapWidth;
    short mapHeight; */

    //level.GetDimensions(mapWidth, mapHeight);

	//int marginX = X_SCREEN_RESOLUTION / 2;
    //int marginY = Y_SCREEN_RESOLUTION / 2;

	// int targetx = clamp(Tx, marginX, mapWidth - marginX) - X_SCREEN_RESOLUTION / 2;
	//int targety = clamp(Ty, marginY, mapHeight - marginY) - Y_SCREEN_RESOLUTION / 2;

	X = Tx;//smooth ? lerp(targetx, mPosition.X.value, smooth_value) : targetx;
	Y = Ty;//smooth ? lerp(targety, mPosition.Y.value, smooth_value) : targety;
}
