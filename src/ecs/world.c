#include "c2ge/ecs.h"
#include "c2ge/config.h"

#include "../utils.h"

#include <stdlib.h>

void c2ge_initWorld(c2ge_World* world)
{
    world->entityIndexTop = 0;
    world->deletedEntityCount = 0;
    world->deletedEntityAllocated = C2GE_INITIAL_ENTITY_ALLOCATE;
    world->deletedEntities 
        = emalloc(world->deletedEntityAllocated * sizeof(c2ge_entityIndex_t));

    world->entityGenerationAllocated = C2GE_INITIAL_ENTITY_ALLOCATE;
    world->entityGeneration = emalloc(
        world->entityGenerationAllocated * sizeof(c2ge_entityGeneration_t));
    for(c2ge_entityIndex_t e = 0; e < world->entityGenerationAllocated; e++)
        world->entityGeneration[e] = 0;
}

unsigned char c2ge_entityExists(const c2ge_World* world, c2ge_Entity entity)
{
    if(entity.index >= world->entityIndexTop)
        return 0;
    if(entity.generation != world->entityGeneration[entity.index])
        return 0;
    return 1;
}

c2ge_Entity c2ge_createEntity(c2ge_World* world)
{
    c2ge_Entity entity;

    if(world->deletedEntityCount > 0) {
        entity.index = world->deletedEntities[--world->deletedEntityCount];
    } else {
        entity.index = world->entityIndexTop++;
    }

    if(world->entityGenerationAllocated < entity.index) {
        uint32_t newAllocated
            = (entity.index / C2GE_ENTITY_ALLOCATE_STEP + 1) 
            * C2GE_ENTITY_ALLOCATE_STEP;
        world->entityGeneration = erealloc(
            world->entityGeneration,
            newAllocated * sizeof(c2ge_entityGeneration_t));
        for(uint32_t i = world->entityGenerationAllocated; i < newAllocated; i++)
            world->entityGeneration[i] = 0;
        world->entityGenerationAllocated = newAllocated;
    }
    entity.generation = world->entityGeneration[entity.index];

    return entity;
}

void c2ge_deleteEntity(c2ge_World* world, c2ge_Entity entity)
{
    if(!c2ge_entityExists(world, entity))
        return;
    if(entity.index == world->entityIndexTop - 1) {
        world->entityIndexTop--;
        world->entityGeneration[entity.index]++;
        return;
    }
    if(world->deletedEntityCount == world->deletedEntityAllocated) {
        uint32_t newAllocated 
            = world->deletedEntityAllocated + C2GE_ENTITY_ALLOCATE_STEP;
        world->deletedEntities = erealloc(
            world->deletedEntities,
            newAllocated * sizeof(c2ge_entityIndex_t));
    }
    world->deletedEntities[world->deletedEntityCount++] = entity.index;
    world->entityGeneration[entity.index]++;
}

void c2ge_destroyWorld(c2ge_World* world)
{
    free(world->deletedEntities);
    free(world->entityGeneration);
}
