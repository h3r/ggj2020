#pragma once

#include "Camera.hpp"
#include "GlobalData.hpp"

enum TileType{
    SCENARIO = 0,
    PLAYER = 1,
    PLAYER_COPY = 2,
    DAMAGE = 3
};

class GameEntity
{
public:
    GameEntity(bool active, short w, short h);
    virtual void Update(GlobalData &gData) = 0;
    virtual void Render(const Camera &cam) = 0;
    bool isActive() const;
    void getPos(short &x, short &y) const;
    void setPos(short x, short y);
    TileType type;
    void getDimensions(short &w, short &h) const;
    short getWidth() const;
    short getHeight() const;
    virtual bool Collides(const GameEntity &other, short x, short y) const;

protected:
    bool active;
    short x, y;
    const short w, h;
};
