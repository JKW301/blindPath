#include "../common.h"

#include "../system/atlas.h"
#include "glass.h"

void initGlass(Entity *e)
{
	e->texture = getAtlasImage("gfx/entities/glass.png", 1);
	e->base = -1;
}
