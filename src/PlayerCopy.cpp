#include "PlayerCopy.hpp"
#include "GameEntity.hpp"
#include "Player.hpp"
#include <stdlib.h>
#include <stddef.h>

#define MAX_SPAWN_TIME 300

PlayerCopy::PlayerCopy(const Player &pl) :
    GameEntity(false, pl.getWidth(), pl.getHeight()),
    pl(pl),
    spawn_timer(rand() % MAX_SPAWN_TIME)
{
}

void PlayerCopy::Update(GlobalData &gData)
{
    (void)gData;

    if (spawn_timer)
        spawn_timer--;
    else
    {
        // Create copy!
        active = true;

        const short *last_x_buf, *last_y_buf;
        const GsSprite *spr_buf;

        pl.GetLastMovements(&last_x_buf, &last_y_buf, &spr_buf);

        if (last_x_buf && last_y_buf && spr_buf)
        {
            const short x = last_x_buf[rand() % LAST_MOVEMENTS_BUF_SIZE];
            const short y = last_y_buf[rand() % LAST_MOVEMENTS_BUF_SIZE];
            spr = spr_buf[rand() % LAST_MOVEMENTS_BUF_SIZE];

            setPos(x, y);
        }
    }
}

void PlayerCopy::Render(const Camera &cam)
{
    if (active)
    {
        getPos(spr.x, spr.y);
        cam.getPosition(spr.x, spr.y);

        GfxSortSprite(&spr);
    }
}
