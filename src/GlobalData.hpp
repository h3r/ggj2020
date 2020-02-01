#pragma once

class Player;
class Enemy;
class Planet;
class Camera;
class CollectableSource;
class Blaster;
class Earth;
template<class T>
class ArrayManager;

#define ARRAY_SIZE(a)   (sizeof (a) / sizeof (a[0]))

struct GlobalData
{
    ArrayManager<Player> &Players;
    Camera &camera;
};
