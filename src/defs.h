

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define PI 3.14159265358979323846

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define FPS        60.0
#define LOGIC_RATE (FPS / 1000)

#define MAX_NAME_LENGTH        32
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_FILENAME_LENGTH    256
#define MAX_LINE_LENGTH        1024
#define MAX_INPUT_LENGTH    16


#define NUM_ATLAS_BUCKETS 64
#define MAX_MOUSE_BUTTONS 8
#define MAX_KEYBOARD_KEYS 350
#define MAX_SND_CHANNELS 16

#define MAP_SIZE 96

#define TILE_HEIGHT 30
#define TILE_WIDTH  60

#define MAP_RENDER_SIZE 24

#define MAP_RENDER_OFFSET_X ((SCREEN_WIDTH - (TILE_WIDTH * MAP_RENDER_SIZE)) / 2)
#define MAP_RENDER_OFFSET_Y 425

#define TILE_WATER  0
#define TILE_GROUND 10
#define TILE_WALL   20

#define EF_NONE                   0
#define EF_SOLID                  (2 << 0)

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	LAYER_BACKGROUND,
	LAYER_MID = 5,
	LAYER_FOREGROUND = 10
};

enum
{
	FACING_NORTH,
	FACING_EAST,
	FACING_SOUTH,
	FACING_WEST,
	FACING_MAX
};

enum
{
	WT_BUTTON,
	WT_SELECT,
	WT_SLIDER,
	WT_INPUT,
	WT_CONTROL,
};

enum
{
	SND_LASER,
	SND_GUI,
	SND_MAX
};
