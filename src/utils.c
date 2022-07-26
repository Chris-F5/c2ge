#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

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

void die(const char* format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    fprintf(stderr, "[C2GE ERROR] ");
    vfprintf(stderr, format, vargs);
    fprintf(stderr, "\n");
    va_end(vargs);
    exit(1);
}
