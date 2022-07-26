#include <stdio.h>
#include <stdlib.h>

#include <c2ge/media.h>

int main()
{
    c2ge_MediaCtx* media = malloc(sizeof(c2ge_MediaCtx));
    if(media == NULL) {
        fprintf(stderr, "failed to allocate media context\n");
        exit(1);
    }

    c2ge_initMediaCtx(media, "top down shooter", 500, 500, 5);
    c2ge_spriteSheetID_t spriteSheet = c2ge_loadSpriteSheet(media, "./assets/sprite_sheet.png", 8, 8);

    while(media->quit == 0) {
        c2ge_handleMediaEvents(media);

        c2ge_clearScreen(media);
        c2ge_drawSprite(media, spriteSheet, 0, 10, 10);
        c2ge_drawSprite(media, spriteSheet, 1, 18, 9);
        c2ge_drawSprite(media, spriteSheet, 2, 24, 10);
        c2ge_drawSprite(media, spriteSheet, 3, 10, 18);
        c2ge_drawSprite(media, spriteSheet, 4, 18, 19);
        c2ge_drawSprite(media, spriteSheet, 5, 24, 18);
        c2ge_presentScreen(media);
    }

    c2ge_destroyMediaCtx(media);

    return 0;
}

