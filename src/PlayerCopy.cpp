#include "PlayerCopy.hpp"
#include "GameEntity.hpp"
#include "Player.hpp"
#include "Utils.h"
#include <stdlib.h>
#include <stddef.h>

#define MIN_SPAWN_TIME 1000
#define MAX_SPAWN_TIME 6000

PlayerCopy::PlayerCopy(const Player &pl) :
    GameEntity(false, pl.getWidth(), pl.getHeight()),
    pl(pl),
    spawn_timer(0),
    timer_running(false)
{
}

void PlayerCopy::StartTimer()
{
    spawn_timer = rand_min_max(MIN_SPAWN_TIME, MAX_SPAWN_TIME);
    timer_running = true;
    printf("Started copy timer with %d ticks\n", spawn_timer);
}

void PlayerCopy::Trigger(GlobalData &gData)
{
    if (pl.isActive())
    {
        printf("Copy triggered!\n");
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

        gData.pl[pl.getId()].plcopies.StartFirst();
    }
}

void PlayerCopy::UpdateInactive(GlobalData &gData)
{
    (void)gData;

    if (timer_running && pl.isActive())
    {
        if (spawn_timer)
            spawn_timer--;
        else if (!active)
        {
            // Create copy!
            Trigger(gData);
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
