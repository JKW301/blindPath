#include "../common.h"

#include "../system/atlas.h"
#include "tree.h"

#define MAX_TREES 15

void initTree(Entity *e)
{
	char filename[MAX_FILENAME_LENGTH];

	sprintf(filename, "gfx/entities/tree%d.png", 1 + rand() % 3);

	e->base = -1;
	e->flags = EF_SOLID;
	e->texture = getAtlasImage(filename, 1);
}