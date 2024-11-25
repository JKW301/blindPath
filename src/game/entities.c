#include "../common.h"

#include "entityFactory.h"
#include "iso.h"
#include "map.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "entities.h"

extern World world;

static void addEntities(void);
static void placeRandom(int *x, int *z);

static AtlasImage *shadowTexture;

void initEntities(void)
{
	memset(&world.entityHead, 0, sizeof(Entity));
	world.entityTail = &world.entityHead;

	addEntities();

	shadowTexture = getAtlasImage("gfx/misc/shadow.png", 1);
}

void drawEntities(void)
{
	Entity *e;
	int     sx, sy;

	for (e = world.entityHead.next; e != NULL; e = e->next)
	{
		sx = TILE_WIDTH / 2;
		sx -= e->texture->rect.w / 2;

		sy = TILE_HEIGHT / 2;
		sy -= e->texture->rect.h;
		sy -= e->base;

		addISOObject(e->x, e->z, sx, sy, e->texture, LAYER_FOREGROUND);

		sx = TILE_WIDTH / 2;
		sx -= shadowTexture->rect.w / 2;

		sy = -shadowTexture->rect.h;
		sy += TILE_HEIGHT;

		addISOObject(e->x, e->z, sx, sy, shadowTexture, LAYER_MID);
	}
}

Entity *getEntityAt(int x, int z)
{
	Entity *e;

	for (e = world.entityHead.next; e != NULL; e = e->next)
	{
		if (e->x == x && e->z == z)
		{
			return e;
		}
	}

	return NULL;
}

static void addEntities(void)
{
	Entity *e;
	int     x, z;

	placeRandom(&x, &z);

	e = initEntity("purpleGuy");
	e->x = x;
	e->z = z;
}

static void placeRandom(int *x, int *z)
{
	int ok;

	do
	{
		*x = rand() % MAP_RENDER_SIZE;
		*z = rand() % MAP_RENDER_SIZE;

		ok = isGround(*x, *z) && getEntityAt(*x, *z) == NULL;
	} while (!ok);
}
