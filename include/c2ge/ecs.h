#ifndef C2GE_ECS_H
#define C2GE_ECS_H

#include <stdint.h>

typedef uint32_t c2ge_entityIndex_t;
typedef uint32_t c2ge_entityGeneration_t;

typedef struct c2ge_Entity c2ge_Entity;
struct c2ge_Entity
{
    c2ge_entityIndex_t index;
    c2ge_entityGeneration_t generation;
};

typedef struct c2ge_World c2ge_World;
struct c2ge_World
{
    c2ge_entityIndex_t entityIndexTop;

    uint32_t deletedEntityCount;
    uint32_t deletedEntityAllocated;
    c2ge_entityIndex_t* deletedEntities;

    uint32_t entityGenerationAllocated;
    c2ge_entityGeneration_t* entityGeneration;
};

void c2ge_initWorld(c2ge_World* world);
void c2ge_destroyWorld(c2ge_World* world);
unsigned char c2ge_entityExists(const c2ge_World* world, c2ge_Entity entity);
c2ge_Entity c2ge_createEntity(c2ge_World* world);
void c2ge_deleteEntity(c2ge_World* world, c2ge_Entity entity);

#endif
