#include "c2ge/id_allocator.h"
#include "c2ge/config.h"

#include "./include.h"

#include <stdlib.h>

int test_IDAllocatorBasic(void)
{
    c2ge_IDAllocator* a = malloc(sizeof(c2ge_IDAllocator));
    c2ge_initIDAllocator(a);
    
    c2ge_id_t id;

    id = c2ge_allocateID(a);
    ASSERT(id == 0);
    ASSERT(c2ge_isIDAllocated(a, 0))
    ASSERT(!c2ge_isIDAllocated(a, 1))
    id = c2ge_allocateID(a);
    ASSERT(id == 1);
    ASSERT(c2ge_isIDAllocated(a, 0))
    ASSERT(c2ge_isIDAllocated(a, 1))
    id = c2ge_allocateID(a);
    ASSERT(id == 2);
    ASSERT(c2ge_isIDAllocated(a, 2))

    c2ge_freeID(a, 1);
    ASSERT(c2ge_isIDAllocated(a, 0))
    ASSERT(!c2ge_isIDAllocated(a, 1))
    ASSERT(c2ge_isIDAllocated(a, 2))
    ASSERT(!c2ge_isIDAllocated(a, 3))

    id = c2ge_allocateID(a);
    ASSERT(id == 1)
    ASSERT(c2ge_isIDAllocated(a, 0))
    ASSERT(c2ge_isIDAllocated(a, 1))
    ASSERT(c2ge_isIDAllocated(a, 2))
    ASSERT(!c2ge_isIDAllocated(a, 3))

    return 0;
}

int test_IDAllocatorMany(void)
{
    c2ge_IDAllocator* a = malloc(sizeof(c2ge_IDAllocator));
    c2ge_initIDAllocator(a);

    c2ge_id_t id;
    for(
        unsigned int i = 0;
        i < C2GE_ID_ALLOCATOR_DELETE_BUFFER_INITIAL 
            + C2GE_ID_ALLOCATOR_DELETE_BUFFER_STEP * 3;
        i++) {
        id = c2ge_allocateID(a);
        ASSERT(id == i)
        ASSERT(c2ge_isIDAllocated(a, id));
        ASSERT(!c2ge_isIDAllocated(a, id + 1))
    }

    c2ge_freeID(a, 10);
    ASSERT(!c2ge_isIDAllocated(a, 10))
    id = c2ge_allocateID(a);
    ASSERT(id == 10)

    for(
        unsigned int i = 0;
        i < C2GE_ID_ALLOCATOR_DELETE_BUFFER_INITIAL
            + C2GE_ID_ALLOCATOR_DELETE_BUFFER_STEP * 2;
        i++) {
        c2ge_freeID(a, i);
        ASSERT(!c2ge_isIDAllocated(a, i))
        ASSERT(c2ge_isIDAllocated(a, i + 1))
    }
    for(
        unsigned int i = 0;
        i < C2GE_ID_ALLOCATOR_DELETE_BUFFER_INITIAL
            + C2GE_ID_ALLOCATOR_DELETE_BUFFER_STEP * 2;
        i++) {
        id = c2ge_allocateID(a);
        ASSERT(c2ge_isIDAllocated(a, id))
        ASSERT(
            id < C2GE_ID_ALLOCATOR_DELETE_BUFFER_INITIAL 
                + C2GE_ID_ALLOCATOR_DELETE_BUFFER_STEP * 2)
    }

    ASSERT(a->deletedCount == 0)

    return 0;
}
