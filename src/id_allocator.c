#include "c2ge/id_allocator.h"
#include "c2ge/config.h"

#include "./utils.h"

#include <stdlib.h>

void c2ge_initIDAllocator(c2ge_IDAllocator* allocator)
{
    allocator->topID = 0;
    allocator->deletedCount = 0;
    allocator->deletedAllocated = C2GE_ID_ALLOCATOR_DELETE_BUFFER_INITIAL;
    allocator->deleted 
        = emalloc(allocator->deletedAllocated * sizeof(c2ge_id_t));
}

void c2ge_destroyIDAllocator(c2ge_IDAllocator* allocator)
{
    free(allocator->deleted);
}

unsigned char c2ge_isIDAllocated(
    const c2ge_IDAllocator* allocator,
    c2ge_id_t id)
{
    if(id >= allocator->topID)
        return 0;
    for(unsigned int i = 0; i < allocator->deletedCount; i++)
        if(allocator->deleted[i] == id)
            return 0;
    return 1;
}

c2ge_id_t c2ge_allocateID(c2ge_IDAllocator* allocator)
{
    if(allocator->deletedCount == 0)
        return allocator->topID++;
    return allocator->deleted[--allocator->deletedCount];
}

void c2ge_freeID(c2ge_IDAllocator* allocator, c2ge_id_t id)
{
    if(!c2ge_isIDAllocated(allocator, id))
        return;
    if(id == allocator->topID - 1) {
        allocator->topID--;
        return;
    }
    if(allocator->deletedCount == allocator->deletedAllocated)
        allocator->deleted = erealloc(
            allocator->deleted,
            (allocator->deletedAllocated += C2GE_ID_ALLOCATOR_DELETE_BUFFER_STEP)
            * sizeof(c2ge_id_t));
    allocator->deleted[allocator->deletedCount++] = id;
}
