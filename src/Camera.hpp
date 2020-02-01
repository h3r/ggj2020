#pragma once

#include "Vector2.hpp"

// class Player;

class Player;

class Camera
{
public:
    
    Camera();
    Camera(const Vector2& initialPos);

    void Default();
    
    void getPosition(short& x, short& y) const;

    void Update();
    void Shake(unsigned int amount, unsigned int length);
    void LookAt(const Vector2& position, bool smoothing = false);

private:
    
    Vector2 mPosition;

    bool smoothing;
    float smooth_value;

    unsigned int shake_elapsed;
	unsigned int shake_length;
	unsigned int shake_amount;

};
