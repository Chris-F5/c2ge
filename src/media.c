#include "c2ge/media.h"

#include <stdio.h>
#include "./utils.h"

#define EVENT_HANDLE_PARAMS c2ge_MediaCtx* media, SDL_Event* event

void handleEvent_Quit(EVENT_HANDLE_PARAMS);

void (*eventHandlers[])(EVENT_HANDLE_PARAMS) = {
    [SDL_QUIT] = handleEvent_Quit,
};

static int mediaCtxInstances = 0;

void c2ge_initMediaCtx(c2ge_MediaCtx* media, const char* title, int width, int height)
{
    if(mediaCtxInstances++ == 1)
        die("does not support multiple media contexts");

    media->quit = 0;

    const char* err;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        err = SDL_GetError();
        die("failed to init SDL2 '%s'", err);
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

}

void c2ge_destroyMediaCtx(c2ge_MediaCtx* media)
{
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

void handleEvent_Quit(EVENT_HANDLE_PARAMS)
{
    media->quit = 1;
}
