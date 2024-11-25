#include "../common.h"

#include "../system/text.h"
#include "hud.h"
int timer = 200 * FPS;
Uint32 lastTick = 0;
extern World world;
int score = 0;
char text[64];

static void drawInfo(void);

void drawHud(void) { drawInfo(); }

static void drawInfo(void) { 

    sprintf(text, "%d,%d", world.cursor.x, world.cursor.z);
    drawText(text, 25, 50, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

    sprintf(text, "Temps restant : %d", (int)round(timer / FPS));
    drawText(text, 25, 75, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

    sprintf(text, "Score: %d", world.score);
    drawText(text, 25, 100, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
}