#include <stdio.h>
#include <flecs.h>

int main()
{
    printf("Hello, World!\n");
    
    ecs_world_t* world = ecs_init();
    
    ecs_fini(world);
    
    printf("Goodbye!\n");
    
    return 0;
}
