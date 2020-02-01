#pragma once

#include "Camera.hpp"
#include "GlobalData.hpp"

class GameEntity
{
public:
    explicit GameEntity(bool active);
    virtual void Update(GlobalData &gData) = 0;
    virtual void Render(const Camera &cam) = 0;
    bool isActive() const;

protected:
    bool active;
};
