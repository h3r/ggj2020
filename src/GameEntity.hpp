#pragma once

#include "Camera.hpp"
#include "GlobalData.hpp"

class GameEntity
{
public:
    GameEntity(bool active, short w, short h);
    virtual void Update(GlobalData &gData) = 0;
    virtual void Render(const Camera &cam) = 0;
    bool isActive() const;
    void getPos(short &x, short &y) const;
    void setPos(short x, short y);
    void getDimensions(short &w, short &h) const;
    virtual bool Collides(const GameEntity &other, short x, short y);

protected:
    bool active;
    short x, y;
    const short w, h;
};
