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
    void getPos(short &x, short &y) const;
    void setPos(short x, short y);

protected:
    bool active;
    short x, y;
};
