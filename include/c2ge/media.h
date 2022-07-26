#ifndef C2GE_MEDIA_H
#define C2GE_MEDIA_H

#include <SDL2/SDL.h>

#define C2GE_MAX_SPRITE_SHEETS 16

typedef uint32_t c2ge_spriteSheetID_t;
typedef uint32_t c2ge_spriteID_t;

typedef struct c2ge_SpriteSheet c2ge_SpriteSheet;
struct c2ge_SpriteSheet {
    const char* fname;
    int spriteWidth, spriteHeight;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int cols, spriteCount;
};

typedef struct c2ge_MediaCtx c2ge_MediaCtx;
struct c2ge_MediaCtx
{
    unsigned char quit;
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned int spriteSheetCount;
    c2ge_SpriteSheet* spriteSheets;
    int scale;
};

void c2ge_initMediaCtx(
    c2ge_MediaCtx* media,
    const char* title,
    int width,
    int height,
    int scale);
void c2ge_destroyMediaCtx(c2ge_MediaCtx* media);
void c2ge_handleMediaEvents(c2ge_MediaCtx* media);

void c2ge_clearScreen(c2ge_MediaCtx* media);
void c2ge_drawSprite(
    c2ge_MediaCtx* media,
    c2ge_spriteSheetID_t spriteSheetID,
    c2ge_spriteID_t spriteID,
    int x,
    int y);
void c2ge_presentScreen(c2ge_MediaCtx* media);

c2ge_spriteSheetID_t c2ge_loadSpriteSheet(
    c2ge_MediaCtx* media,
    const char* fname,
    int spriteWidth,
    int spriteHeight);

#endif
