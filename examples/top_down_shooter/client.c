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

    c2ge_initMediaCtx(media, "top down shooter", 500, 500);

    while(media->quit == 0) {
        c2ge_handleMediaEvents(media);
    }

    c2ge_destroyMediaCtx(media);

    return 0;
}

