#include "c2ge/media.h"

#include <stdio.h>
#include <SDL2/SDL_image.h>

#include "./utils.h"

#define EVENT_HANDLE_PARAMS c2ge_MediaCtx* media, SDL_Event* event

static void handleEvent_Quit(EVENT_HANDLE_PARAMS);

static void (*eventHandlers[])(EVENT_HANDLE_PARAMS) = {
    [SDL_QUIT] = handleEvent_Quit,
};

static int mediaCtxInstances = 0;

static void handleEvent_Quit(EVENT_HANDLE_PARAMS)
{
    media->quit = 1;
}

static void destroySpriteSheet(c2ge_SpriteSheet* spriteSheet)
{
    SDL_FreeSurface(spriteSheet->surface);
    SDL_DestroyTexture(spriteSheet->texture);
}

static SDL_Rect getSpriteRect(c2ge_SpriteSheet* spriteSheet, c2ge_spriteID_t id)
{
    SDL_Rect rect;
    rect.w = spriteSheet->spriteWidth;
    rect.h = spriteSheet->spriteHeight;
    rect.x = (id % spriteSheet->cols) * spriteSheet->spriteWidth;
    rect.y = (id / spriteSheet->cols) * spriteSheet->spriteHeight;
    return rect;
}

void c2ge_initMediaCtx(
    c2ge_MediaCtx* media,
    const char* title,
    int width,
    int height,
    int scale)
{
    if(mediaCtxInstances++ == 1)
        die("does not support multiple media contexts");

    media->quit = 0;

    const char* err;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        err = SDL_GetError();
        die("failed to init SDL2 '%s'", err);
    }
    if(IMG_Init(IMG_INIT_PNG) < 0) {
        err = IMG_GetError();
        die("failed to init SDL2_IMG '%s'", err);
    }

    media->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN);
    if(media->window == NULL) {
        err = SDL_GetError();
        die("failed to create SDL2 window '%s'", err);
    }

    media->renderer = SDL_CreateRenderer(
        media->window,
        -1,
        SDL_RENDERER_ACCELERATED);
    if(media->renderer == NULL) {
        err = SDL_GetError();
        die("failed to create SDL2 renderer '%s'", err);
    }

    media->spriteSheetCount = 0;
    media->spriteSheets 
        = emalloc(C2GE_MAX_SPRITE_SHEETS * sizeof(c2ge_SpriteSheet));
    media->scale = scale;
}

void c2ge_destroyMediaCtx(c2ge_MediaCtx* media)
{
    for(uint32_t i = 0; i < media->spriteSheetCount; i++) {
        destroySpriteSheet(&media->spriteSheets[i]);
    }
    free(media->spriteSheets);
    SDL_DestroyRenderer(media->renderer);
    SDL_DestroyWindow(media->window);
    SDL_Quit();
}

void c2ge_handleMediaEvents(c2ge_MediaCtx* media)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if(event.type >= sizeof(eventHandlers) / sizeof(eventHandlers[0]))
            continue;
        if(eventHandlers[event.type])
            eventHandlers[event.type](media, &event);
    }
}

void c2ge_clearScreen(c2ge_MediaCtx* media)
{
    SDL_SetRenderDrawColor(media->renderer, 0, 0, 0, 0);
    SDL_RenderClear(media->renderer);
}

void c2ge_drawSprite(
    c2ge_MediaCtx* media,
    c2ge_spriteSheetID_t spriteSheetID,
    c2ge_spriteID_t spriteID,
    int x,
    int y)
{
    c2ge_SpriteSheet* spriteSheet = &media->spriteSheets[spriteSheetID];
    SDL_Rect srcRect, dstRect;
    if(spriteSheetID >= media->spriteSheetCount)
        die("failed to draw sprite. invalid sprite sheet id '%d'", spriteSheetID);
    srcRect = getSpriteRect(spriteSheet, spriteID);

    dstRect.x = x * media->scale;
    dstRect.y = y * media->scale;
    dstRect.w = spriteSheet->spriteWidth * media->scale; 
    dstRect.h = spriteSheet->spriteHeight * media->scale; 
    SDL_RenderCopy(
        media->renderer,
        spriteSheet->texture,
        &srcRect,
        &dstRect);
}

void c2ge_presentScreen(c2ge_MediaCtx* media)
{
    SDL_RenderPresent(media->renderer);
}

c2ge_spriteSheetID_t c2ge_loadSpriteSheet(
    c2ge_MediaCtx* media,
    const char* fname,
    int spriteWidth,
    int spriteHeight)
{
    c2ge_spriteSheetID_t ref = media->spriteSheetCount++;
    if(media->spriteSheetCount >= C2GE_MAX_SPRITE_SHEETS)
        die("exceeded max sprite sheet count (%d)", C2GE_MAX_SPRITE_SHEETS);
    c2ge_SpriteSheet* spriteSheet = &media->spriteSheets[ref];

    spriteSheet->spriteWidth = spriteWidth;
    spriteSheet->spriteHeight = spriteHeight;
    spriteSheet->surface = IMG_Load(fname);
    const char* err;
    if(spriteSheet->surface == NULL) {
        err = IMG_GetError();
        die("failed to load sprite sheet image '%s'", err);
    }
    spriteSheet->cols = spriteSheet->surface->w / spriteSheet->spriteWidth;
    spriteSheet->spriteCount 
        = spriteSheet->cols
        * (spriteSheet->surface->h / spriteSheet->spriteHeight);

    spriteSheet->texture = SDL_CreateTextureFromSurface(
        media->renderer,
        spriteSheet->surface);
    if(spriteSheet->texture == NULL) {
        err = SDL_GetError();
        die("failed to create sprite sheet texture '%s'", err);
    }

    return ref;
}
