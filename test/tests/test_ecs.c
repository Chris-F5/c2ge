#include "c2ge/ecs.h"
#include "c2ge/config.h"

#include "./include.h"

#include <stdlib.h>

int test_entityAllocation(void)
{
    c2ge_World* world = malloc(sizeof(c2ge_World));
    ASSERT(world != NULL);
    c2ge_initWorld(world);

    c2ge_Entity entity;

    /* CREATE ENTITIES */
    int entityCount 
        = C2GE_INITIAL_ENTITY_ALLOCATE + C2GE_ENTITY_ALLOCATE_STEP + 5;

    for(int i = 0; i < entityCount; i++) {
        entity = c2ge_createEntity(world);
        ASSERT(entity.index == i);
        ASSERT(entity.generation == 0);
    }

    /* DELETE AND INSERT IN MIDDLE */
    int testEntityIndex = C2GE_INITIAL_ENTITY_ALLOCATE + 3;
    entity.index = testEntityIndex;
    entity.generation = 0;
    ASSERT(c2ge_entityExists(world, entity));

    c2ge_deleteEntity(world, entity);
    ASSERT(!c2ge_entityExists(world, entity));

    entity = c2ge_createEntity(world);
    ASSERT(entity.index == testEntityIndex);
    ASSERT(entity.generation == 1);
    ASSERT(c2ge_entityExists(world, entity));

    /* TOP ENTITY */
    entity = c2ge_createEntity(world);
    ASSERT(entity.index == entityCount);
    ASSERT(entity.generation == 0);
    ASSERT(c2ge_entityExists(world, entity));

    c2ge_deleteEntity(world, entity);
    ASSERT(!c2ge_entityExists(world, entity));

    entity = c2ge_createEntity(world);
    ASSERT(entity.index == entityCount);
    ASSERT(entity.generation == 1);
    ASSERT(c2ge_entityExists(world, entity));

    /* DELETE MULTIPLE */
    int i;
    for(i = 1 ; i < entityCount; i += 3) {
        entity.index = i;
        entity.generation = world->entityGeneration[i];
        c2ge_deleteEntity(world, entity);
        ASSERT(!c2ge_entityExists(world, entity));
    }

    for(i -= 3; i >= 1; i -= 3) {
        entity = c2ge_createEntity(world);
        ASSERT(entity.index == i);
    }

    c2ge_destroyWorld(world);

    return 0;
}
