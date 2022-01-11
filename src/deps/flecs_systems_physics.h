// Comment out this line when using as DLL
#define flecs_systems_physics_STATIC
#ifndef FLECS_SYSTEMS_PHYSICS_H
#define FLECS_SYSTEMS_PHYSICS_H

/* This generated file contains includes for project dependencies */
/*
                                   )
                                  (.)
                                  .|.
                                  | |
                              _.--| |--._
                           .-';  ;`-'& ; `&.
                          \   &  ;    &   &_/
                           |"""---...---"""|
                           \ | | | | | | | /
                            `---.|.|.|.---'

 * This file is generated by bake.lang.c for your convenience. Headers of
 * dependencies will automatically show up in this file. Include bake_config.h
 * in your main project file. Do not edit! */

#ifndef FLECS_SYSTEMS_PHYSICS_BAKE_CONFIG_H
#define FLECS_SYSTEMS_PHYSICS_BAKE_CONFIG_H

/* Headers of public dependencies */
#include <flecs.h>
#include "cglm.h"
#include "flecs_components_transform.h"
#include "flecs_components_geometry.h"
#include "flecs_components_physics.h"

/* Convenience macro for exporting symbols */
#ifndef flecs_systems_physics_STATIC
#if flecs_systems_physics_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
  #define FLECS_SYSTEMS_PHYSICS_API __declspec(dllexport)
#elif flecs_systems_physics_EXPORTS
  #define FLECS_SYSTEMS_PHYSICS_API __attribute__((__visibility__("default")))
#elif defined _MSC_VER
  #define FLECS_SYSTEMS_PHYSICS_API __declspec(dllimport)
#else
  #define FLECS_SYSTEMS_PHYSICS_API
#endif
#else
  #define FLECS_SYSTEMS_PHYSICS_API
#endif

#endif


#ifndef FLECS_SYSTEMS_PHYSICS_OCTREE_H
#define FLECS_SYSTEMS_PHYSICS_OCTREE_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ecs_octree_t ecs_octree_t;

typedef struct ecs_oct_entity_t {
    ecs_entity_t e;
    vec3 pos;
    vec3 size;
} ecs_oct_entity_t;

FLECS_SYSTEMS_PHYSICS_API
ecs_octree_t* ecs_octree_new(
    vec3 center,
    float size);

FLECS_SYSTEMS_PHYSICS_API
void ecs_octree_free(
    ecs_octree_t *ot);

FLECS_SYSTEMS_PHYSICS_API
void ecs_octree_clear(
    ecs_octree_t *ot);    

FLECS_SYSTEMS_PHYSICS_API
int32_t ecs_octree_insert(
    ecs_octree_t *ot,
    ecs_entity_t e,
    vec3 pos,
    vec3 size);

FLECS_SYSTEMS_PHYSICS_API
void ecs_octree_findn(
    ecs_octree_t *ot,
    vec3 pos,
    float range,
    ecs_vector_t **result);

FLECS_SYSTEMS_PHYSICS_API
int32_t ecs_octree_dump(
    ecs_octree_t *ot);

#ifdef __cplusplus
}
#endif

#endif

#ifndef FLECS_SYSTEMS_PHYSICS_SQUERY_H
#define FLECS_SYSTEMS_PHYSICS_SQUERY_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ecs_squery_t ecs_squery_t;

FLECS_SYSTEMS_PHYSICS_API
ecs_squery_t* ecs_squery_new(
    ecs_world_t *world,
    const char *expr,
    vec3 center,
    float size);

FLECS_SYSTEMS_PHYSICS_API
void ecs_squery_free(
    ecs_squery_t *sq);

FLECS_SYSTEMS_PHYSICS_API
void ecs_squery_update(
    ecs_squery_t *sq);    

FLECS_SYSTEMS_PHYSICS_API
void ecs_squery_findn(
    const ecs_squery_t *sq,
    vec3 position,
    float range,
    ecs_vector_t **result);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

namespace flecs {

class squery {
public:
    using entity = ecs_oct_entity_t;

    squery() {
        sq_ = nullptr;
    }

    squery(flecs::world& world, const char *expr, vec3 center, float size) {
        sq_ = ecs_squery_new(world.c_ptr(), expr, center, size);
    }

    void update() {
        ecs_squery_update(sq_);
    }

    void findn(vec3 pos, float range, flecs::vector<squery::entity>& results) const {
        ecs_vector_t *v = results.ptr();
        ecs_squery_findn(sq_, pos, range, &v);
        results.ptr(v);
    }

private:
    ecs_squery_t *sq_;
};

}

#endif

#endif


// Don't use reflection, but use utility macro's for auto-exporting variables
#undef ECS_META_IMPL
#ifndef FLECS_SYSTEMS_PHYSICS_IMPL
#define ECS_META_IMPL EXTERN
#else
#define ECS_META_IMPL DECLARE
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus

ECS_STRUCT(EcsSpatialQuery, {
    ecs_squery_t *query;
});

ECS_STRUCT(EcsSpatialQueryResult, {
    ecs_vector_t *results;
});

#else

typedef struct EcsSpatialQuery {
    flecs::squery query;
} EcsSpatialQuery;

typedef struct EcsSpatialQueryResult {
    flecs::vector<flecs::squery::entity> results;
} EcsSpatialQueryResult;

#endif

FLECS_SYSTEMS_PHYSICS_API
void FlecsSystemsPhysicsImport(
    ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

namespace flecs {
namespace systems {

class physics : FlecsSystemsPhysics {
public:
    using SpatialQuery = EcsSpatialQuery;
    using SpatialQueryResult = EcsSpatialQueryResult;

    physics(flecs::world& ecs) {
        FlecsSystemsPhysicsImport(ecs.c_ptr());

        ecs.module<flecs::systems::physics>();

        ecs.component<SpatialQuery>("flecs::systems::physics::SpatialQuery");
        ecs.component<SpatialQueryResult>("flecs::systems::physics::SpatialQueryResult");
    }
};

}
}

#endif

#endif

