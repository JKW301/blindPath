

typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;
typedef struct Entity     Entity;
typedef struct InitFunc   InitFunc;
typedef struct Node       Node;
typedef struct Widget     Widget;

struct Widget
{
	int     type;
	char    name[MAX_NAME_LENGTH];
	int     x;
	int     y;
	int     w;
	int     h;
	char    label[MAX_NAME_LENGTH];
	Widget *prev;
	Widget *next;
	void (*action)(void);
	void(*data);
};

typedef struct
{
	int    numOptions;
	char **options;
	int    x;
	int    y;
	int    value;
} SelectWidget;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int value;
	int step;
	int waitOnChange;
} SliderWidget;

typedef struct
{
	int   x;
	int   y;
	int   maxLength;
	char *text;
} InputWidget;

typedef struct
{
	int x;
	int y;
	int value;
} ControlWidget;

struct AtlasImage
{
	char         filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect     rect;
	int          rotated;
	AtlasImage  *next;
};

struct Texture
{
	char         name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture     *next;
};

struct InitFunc
{
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

struct Node
{
	int   x;
	int   z;
	int   g;
	int   f;
	int   h;
	int   closed;
	Node *parent;
	Node *next;
};

typedef struct
{
	int         x;
	int         y;
	int         sx;
	int         sy;
	int         layer;
	AtlasImage *texture;
} ISOObject;

struct Entity
{
	char        name[MAX_NAME_LENGTH];
	int         x;
	int         z;
	int         base;
	int flags;
	AtlasImage *texture;
	Entity     *next;

};

typedef struct
{
	int tile;
	int hasTree;
} MapTile;

typedef struct
{
	char        name[MAX_NAME_LENGTH];

} Player;

typedef struct {
	MapTile map[MAP_SIZE][MAP_SIZE];
	Entity entityHead, *entityTail;
	Node routeHead;
	Entity *player;
	SDL_Rect playerISORect;
	struct {
		int x;
		int z;
	} cursor;
	struct {
		int x;
		int z;
	} camera;
	int score;
} World;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int           keyboard[MAX_KEYBOARD_KEYS];
	double        deltaTime;
	double        fontScale;
	Widget       *activeWidget;
	char          inputText[MAX_INPUT_LENGTH];
	int           lastKeyPressed;
	struct
	{
		int x;
		int y;
		int buttons[MAX_MOUSE_BUTTONS];
		int visible;
	} mouse;
	struct
	{
		int fps;
		int showFPS;
	} dev;
} App;
