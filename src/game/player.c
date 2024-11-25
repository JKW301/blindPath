#include "../common.h"

#include "../game/aStar.h"
#include "../system/atlas.h"
#include "player.h"
#include "map.h"

#define WALK_SPEED 5

extern App   app;
extern World world;
extern int   timer;

static AtlasImage *textures[FACING_MAX];
static double      walkTimer;

void initPlayer(void)
{
	textures[FACING_NORTH] = textures[FACING_EAST] = getAtlasImage("gfx/entities/purpleGuyNorthEast.png", 1);
	textures[FACING_SOUTH] = getAtlasImage("gfx/entities/purpleGuySouth.png", 1);
	textures[FACING_WEST] = getAtlasImage("gfx/entities/purpleGuyWest.png", 1);

	world.player->texture = textures[FACING_SOUTH];

	walkTimer = 0;
	world.player->x = 0;
	world.player->z = 11;
}

void doPlayer(void)
{
    if (timer <= 0) {
        return;
    }

    Node *n;
    int   dx, dz, facing;

    walkTimer = MAX(walkTimer - app.deltaTime, 0);

    if (world.routeHead.next == NULL)
    {
        if (app.mouse.buttons[SDL_BUTTON_LEFT])
        {
            app.mouse.buttons[SDL_BUTTON_LEFT] = 0;


             if (world.map[world.cursor.x][world.cursor.z].tile != TILE_RANDOM_PATH && world.map[world.cursor.x][world.cursor.z].tile != TILE_EXIT) {
                world.player->x = PLAYER_START_X;
                world.player->z = PLAYER_START_Z;
                return;
            }

            createAStarRoute(world.player, world.cursor.x, world.cursor.z);

            walkTimer = WALK_SPEED;
        }
    }
    else if (walkTimer == 0)
    {
        n = world.routeHead.next;

        dx = n->x - world.player->x;
        dz = n->z - world.player->z;

        facing = (90 + (atan2(dz, dx) * 180 / PI)) / 90;
        facing %= FACING_MAX;

        world.player->texture = textures[facing];

        world.player->x = n->x;
        world.player->z = n->z;

        world.routeHead.next = n->next;

        free(n);

        walkTimer = WALK_SPEED;
    }
}