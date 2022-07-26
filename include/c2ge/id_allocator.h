#ifndef C2GE_ID_ALLOCATOR_H
#define C2GE_ID_ALLOCATOR_H

#include <stdint.h>

typedef uint32_t c2ge_id_t;

typedef struct c2ge_IDAllocator c2ge_IDAllocator;
struct c2ge_IDAllocator
{
    c2ge_id_t topID;

    unsigned int deletedCount;
    unsigned int deletedAllocated;
    c2ge_id_t* deleted;
};

void c2ge_initIDAllocator(c2ge_IDAllocator* allocator);
void c2ge_destroyIDAllocator(c2ge_IDAllocator* allocator);
unsigned char c2ge_isIDAllocated(
    const c2ge_IDAllocator* allocator,
    c2ge_id_t id);
c2ge_id_t c2ge_allocateID(c2ge_IDAllocator* allocator);
void c2ge_freeID(c2ge_IDAllocator* allocator, c2ge_id_t id);

#endif
