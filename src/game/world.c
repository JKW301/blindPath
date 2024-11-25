#include <SDL2/SDL_mixer.h>


#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../game/iso.h"
#include "../game/map.h"
#include "../game/player.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
#include "../system/text.h"
#include "../system/widgets.h"

#include "world.h"


extern Uint32 lastTick;
extern App   app;
extern World world;
extern int timer;
extern int score;
extern char text[64];

static void logic(void);
static void doCursor(void);
static void draw(void);
void drawEndGameText(void);

static void resume(void);
static void name(void);
static void music(void);
static void sound(void);
static void showFPS(void);
static void quit(void);
static void decrement_timer(void);
static void handleExitTile(void);
static void SaveAndQuit(void);
void saveGameState(void);


static Player      player;
static int         paused;


void initWorld(void)
{
	

	initMap();
	initEntities();

	initISORender();

	initPlayer();

	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	Widget       *w;
	InputWidget  *iw;
	SelectWidget *sw;
	SliderWidget *sl;
	
	paused = 0;

	w = getWidget("name");
	w->action = name;
	iw = (InputWidget *)w->data;
	iw->x = 700;
	iw->y = w->y;
	STRNCPY(iw->text, "Player", iw->maxLength);

	app.activeWidget = w;
	app.activeWidget->action();
	
	w = getWidget("sound");
	w->action = sound;
	sl = (SliderWidget *)w->data;
	sl->x = 700;
	sl->y = w->y + 16;
	sl->w = 300;
	sl->h = 32;
	sl->value = 100;

	app.activeWidget = w;
	app.activeWidget->action();

	w = getWidget("music");
	w->action = music;
	sl = (SliderWidget *)w->data;
	sl->x = 700;
	sl->y = w->y + 16;
	sl->w = 300;
	sl->h = 32;
	sl->value = 50;

	app.activeWidget = w;
	app.activeWidget->action();

	w = getWidget("showFPS");
	w->action = showFPS;
	sw = (SelectWidget *)w->data;
	sw->x = 700;
	sw->value = 0;

	app.activeWidget = w;
	app.activeWidget->action();
	
	w = getWidget("SaveAndQuit");
	w->action = SaveAndQuit;


	w = getWidget("exit");
	w->action = quit;

	w = getWidget("resume");
	w->action = resume;


	app.activeWidget = w;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	lastTick = SDL_GetTicks() + 1000;
    if (!paused)
    { 
		handleExitTile();
		decrement_timer();
        doISOObjects();
        doCursor();
        doPlayer();
    }
    else
    {
        doWidgets();
    }
    if (app.keyboard[SDL_SCANCODE_ESCAPE])
    {
        app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
        paused = !paused;
    }
}
static void doCursor(void)
{
	double sx, sy;

	sx = app.mouse.x - (TILE_WIDTH / 2);
	sy = app.mouse.y - (TILE_HEIGHT / 2);

	sx -= MAP_RENDER_OFFSET_X;
	sy -= MAP_RENDER_OFFSET_Y;

	world.cursor.x = round(((sx / TILE_WIDTH) - (sy / TILE_HEIGHT)));
	world.cursor.z = round(((sx / TILE_WIDTH) + (sy / TILE_HEIGHT)));
}

static void draw(void)
{	
	if (!paused)
	{
		drawHud();
		
		clearISOObjects();

		drawMap();

		drawEntities();

		drawISOObjects();

	}
	else
	{
		drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 128);

		drawWidgets();
	}

}
/*
static void drawHud(void)
{
	drawText(player.name, 10, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
}
*/

static void resume(void)
{
	paused = 0;
}

static void name(void)
{
	InputWidget *iw;

	iw = (InputWidget *)app.activeWidget->data;

	STRCPY(player.name, iw->text);
}

static void music(void)
{
	SliderWidget *sw;
	int           vol;

	sw = (SliderWidget *)app.activeWidget->data;

	vol = MIX_MAX_VOLUME * (sw->value * 0.01);

	Mix_VolumeMusic(vol);
}

static void sound(void)
{
	SliderWidget *sw;
	int           vol;

	sw = (SliderWidget *)app.activeWidget->data;

	vol = MIX_MAX_VOLUME * (sw->value * 0.01);

	Mix_Volume(-1, vol);
}

static void showFPS(void)
{
	SelectWidget *sw;

	sw = (SelectWidget *)app.activeWidget->data;

	app.dev.showFPS = sw->value;
}
static void decrement_timer(void) {
    if (timer <= 0) {
        return;
    }

    Uint32 currentTick = SDL_GetTicks();
    if (currentTick - lastTick >= 1000) {
        timer--;
        printf("Timer decremented: %d\n", timer);
        lastTick = currentTick;
    }
}
void handleExitTile(void) {
    if (world.map[world.player->x][world.player->z].tile == TILE_EXIT) {
        initMap();

        world.player->x = 0;
        world.player->z = 11;
		world.score++;
    }
}
void drawEndGameText(void) {
    if (timer <= 0) {
        sprintf(text, "EndGame score: %d", world.score);
        int charWidth = 10;
        int textWidth = strlen(text) * charWidth;
        int x = (SCREEN_WIDTH - textWidth) / 2;
        drawText(text, x, 125, 255, 255, 255, TEXT_ALIGN_CENTER, 0);
    }
}
static void SaveAndQuit(void)
{
    saveGameState();
    SDL_Quit();
    exit(0);
}
static void quit(void)
{
	exit(0);
}
void saveGameState(void)
{
    FILE *file = fopen("savedata.txt", "w"); 

    if (file == NULL)
    {
        perror("Error opening file for saving game state");
        return;
    }

    fprintf(file, "Player Coordinates:\n");
    fprintf(file, "x: %d\n", world.player->x);
    fprintf(file, "z: %d\n", world.player->z);
    fprintf(file, "Timer: %d\n", timer);
    fprintf(file, "Score: %d\n", world.score);

    fclose(file);
}
