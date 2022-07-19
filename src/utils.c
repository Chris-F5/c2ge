#include <stdlib.h>
#include <stdio.h>

void* emalloc(size_t size)
{
    void* p;
    p = malloc(size);
    if(p == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        exit(1);
    }
    return p;
}

void* erealloc(void* ptr, size_t size)
{
    void* p;
    p = realloc(ptr, size);
    if(p == NULL) {
        fprintf(stderr, "failed to reallocate memory\n");
        exit(1);
    }
    return p;
}
