#include "../common.h"

#include "purpleGuy.h"

extern World world;

void initPurpleGuy(Entity *e)
{
    e->base = -13;
    world.player = e;
}
