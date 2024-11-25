#include "../common.h"
#include "../game/iso.h"
#include "../system/atlas.h"
#include "map.h"

#define MAX_TILES 20
#define TILE_PATH 100
#define MAX_PATH_LENGTH 50
#define TILE_GROUND 10
#define MAX_BRANCH_LENGTH 10

extern World world;
extern int timer;
extern char text[64];

static void loadTiles(void);
static void generateRandomPath(void);

static AtlasImage *tiles[MAX_TILES];
static AtlasImage *selectedTileTexture;
static AtlasImage *randomPathTexture;

int lastTileX = 0;
int lastTileZ = 0;

void initMap(void)
{
    int x, z;
    for (x = 0; x < MAP_RENDER_SIZE; x++)
    {
        for (z = 0; z < MAP_RENDER_SIZE; z++)
        {
            world.map[x][z].tile = TILE_GROUND;
        }
    }
    loadTiles();
    generateRandomPath();
    for (x = 0; x < MAP_RENDER_SIZE; x++)
    {
        for (z = 0; z < MAP_RENDER_SIZE; z++)
        {
            if (world.map[x][z].tile == TILE_GROUND)
            {
                world.map[x][z].tile += rand() % 3;
            }
        }
    }
}

int isGround(int x, int z)
{
    return x >= 0 && z >= 0 && x < MAP_SIZE && z < MAP_SIZE && world.map[x][z].tile >= TILE_GROUND && world.map[x][z].tile < TILE_WALL;
}

void drawMap(void)
{
    int x, z, n;

    for (x = 0; x < MAP_RENDER_SIZE; x++)
    {
        for (z = 0; z < MAP_RENDER_SIZE; z++)
        {
            n = world.map[x][z].tile;

            if (n >= 0)
            {
                if (world.routeHead.next == NULL && isGround(x, z) && x == world.cursor.x && z == world.cursor.z)
                {
                    addISOObject(x, z, 0, 0, selectedTileTexture, LAYER_BACKGROUND);
                }
                else
                {
                    if (n == TILE_RANDOM_PATH)
                    {
                        addISOObject(x, z, 0, 0, randomPathTexture, LAYER_BACKGROUND);
                    }
                    else
                    {
                        addISOObject(x, z, 0, 0, tiles[n], LAYER_BACKGROUND);
                    }
                }
            }
        }
    }
}

static void loadTiles(void)
{
    int i;
    char filename[MAX_FILENAME_LENGTH];

    for (i = 0; i < MAX_TILES; i++)
    {
        sprintf(filename, "gfx/tiles/20.png");

        tiles[i] = getAtlasImage(filename, 0);
    }

    selectedTileTexture = getAtlasImage("gfx/tiles/exit.png", 1);
    randomPathTexture = getAtlasImage("gfx/tiles/10.png", 1);
}

static void generateRandomPath(void)
{
    int x = PLAYER_START_X;
    int z = PLAYER_START_Z;
    int direction = rand() % 4;
    int pathLength = 0;
    int sameDirectionCount = 0;
    direction = rand() % 4;
    sameDirectionCount = 0;

    pathLength = 0;

    while (pathLength < MAX_PATH_LENGTH)
    {
        int oldX = x, oldZ = z, oldDirection = direction;
        switch (direction)
        {
            case 0:
                if (x < MAP_RENDER_SIZE - 1) x++;
                break;
            case 1:
                if (z < MAP_RENDER_SIZE - 1) z++;
                break;
            case 2:
                if (x > 0) x--;
                break;
            case 3:
                if (z > 0) z--;
                break;
        }

        if (oldDirection != direction) {
            sameDirectionCount = 0;
        }
        if (world.map[x][z].tile == TILE_GROUND)
        {
            world.map[x][z].tile = TILE_RANDOM_PATH;
            pathLength++;
            sameDirectionCount++;

            lastTileX = x;
            lastTileZ = z;

            if (sameDirectionCount >= 4) {
                direction = rand() % 4;
                sameDirectionCount = 0;
            }
        }
        else
        {
            x = oldX;
            z = oldZ;
            direction = rand() % 4;
        }
    }
    world.map[lastTileX][lastTileZ].tile = TILE_EXIT;
}
