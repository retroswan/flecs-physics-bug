#include <stdio.h>
#include <flecs.h>
#include "deps.h"

static void CollisionsSystem(ecs_iter_t* it)
{
    EcsPosition3* p = ecs_term(it, EcsPosition3, 1);
    EcsSpatialQuery* q = ecs_term(it, EcsSpatialQuery, 2);
    EcsSpatialQueryResult* r = ecs_term(it, EcsSpatialQueryResult, 3);
    
    for(int i = 0; i < it->count; i++)
    {
        ecs_octree_findn(q[i].query, &p[i], 4, &r[i].results);
        for(int j = 0; j < r[i].results->count; j++)
        {
            //
        }
    }
}

int main()
{
    printf("Hello, World!\n");
    
    ecs_world_t* world = ecs_init();
    ecs_set_target_fps(world, 60.0f);
    
    ECS_IMPORT(world, FlecsComponentsPhysics);
    ECS_IMPORT(world, FlecsSystemsPhysics);
    ECS_TAG(world, AABB);
    ECS_SYSTEM(world, CollisionsSystem, EcsPreUpdate, EcsPosition3, (EcsSpatialQuery, AABB), (EcsSpatialQueryResult, AABB));
    
    float size = 1024;
    EcsPosition3 center = {
        .x = size / 2,
        .y = size / 2,
        .z = size / 2,
    };
    
    ecs_entity_t e;
    
    e = ecs_new(world, 0);
    ecs_set(world, e, EcsPosition3, {
        .x = 0,
        .y = 0,
        .z = 0,
    });
    ecs_set(world, e, EcsVelocity3, {
        .x = 0,
        .y = 0,
        .z = 0,
    });
    ecs_set_pair(world, e, EcsSpatialQuery, AABB, { ecs_squery_new(world, "AABB", &center, size), });
    ecs_set_pair(world, e, EcsSpatialQueryResult, AABB, { NULL, });
    
    e = ecs_new(world, 0);
    ecs_set(world, e, EcsPosition3, {
        .x = 16,
        .y = 0,
        .z = 0,
    });
    ecs_set(world, e, EcsVelocity3, {
        .x = 0,
        .y = 0,
        .z = 0,
    });
    ecs_set_pair(world, e, EcsSpatialQuery, AABB, { ecs_squery_new(world, "AABB", &center, size), });
    ecs_set_pair(world, e, EcsSpatialQueryResult, AABB, { NULL, });
    
    while(1)
    {
        ecs_progress(world, 0);
    }
    
    ecs_fini(world);
    
    printf("Goodbye!\n");
    
    return 0;
}
