extern int lastTileX;
extern int lastTileZ;

#define TILE_RANDOM_PATH 101
#define TILE_EXIT 20
#define TILE_10 10

#define PLAYER_START_X 0
#define PLAYER_START_Z 11

void initMap(void);
int  isGround(int x, int z);
void drawMap(void);
