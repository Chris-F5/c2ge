#ifndef C2GE_MEDIA_H
#define C2GE_MEDIA_H

#include <SDL2/SDL.h>

typedef struct c2ge_MediaCtx c2ge_MediaCtx;
struct c2ge_MediaCtx
{
    unsigned int quit;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void c2ge_initMediaCtx(c2ge_MediaCtx* media, const char* title, int width, int height);
void c2ge_destroyMediaCtx(c2ge_MediaCtx* media);
void c2ge_handleMediaEvents(c2ge_MediaCtx* media);

#endif
