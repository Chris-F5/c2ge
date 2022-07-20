#include <stdio.h>
#include <stdlib.h>

#include "c2ge/ecs.h"

void printEntity(c2ge_Entity entity)
{
    printf(
        "Entity {index: %d, generation: %d}\n",
        entity.index,
        entity.generation);
}

int main()
{
    c2ge_World* world = malloc(sizeof(c2ge_World));
    c2ge_Entity entity;

    if(world == NULL) {
        fprintf(stderr, "failed to allocate world");
        exit(1);
    }
    c2ge_initWorld(world);

    printEntity(c2ge_createEntity(world));
    printEntity(entity = c2ge_createEntity(world));
    printf("destroy %d\n", entity.index);
    c2ge_deleteEntity(world, entity);
    printEntity(entity = c2ge_createEntity(world));
    printEntity(c2ge_createEntity(world));
    printf("destroy %d\n", entity.index);
    c2ge_deleteEntity(world, entity);
    printEntity(c2ge_createEntity(world));

    c2ge_destroyWorld(world);
    return 0;
}
