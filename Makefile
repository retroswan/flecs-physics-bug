INCS=-I/home/swan/Programming/Libraries/Debug/flecs-master/include
LIBS=-L/home/swan/Programming/Libraries/Debug/flecs-master -lflecs

.PHONY=build
build:
	make deps
	gcc -g -pedantic -c src/main.c -o src/main.o ${INCS}
	gcc -g -pedantic src/main.o src/deps/*.o -o main ${LIBS} -lm -Wl,-rpath=./

.PHONY=build-deps
deps:
	${CC} ${CFLAGS} -c src/deps/cglm.c -o src/deps/cglm.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_components_cglm.c -o src/deps/flecs_components_cglm.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_components_geometry.c -o src/deps/flecs_components_geometry.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_components_graphics.c -o src/deps/flecs_components_graphics.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_components_physics.c -o src/deps/flecs_components_physics.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_components_transform.c -o src/deps/flecs_components_transform.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_systems_physics.c -o src/deps/flecs_systems_physics.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/flecs_systems_transform.c -o src/deps/flecs_systems_transform.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/octree.c -o src/deps/octree.o ${INCS}
	${CC} ${CFLAGS} -c src/deps/spatial_query.c -o src/deps/spatial_query.o ${INCS}

.PHONY=clean
clean:
	rm -f src/*.o
	rm -f src/**/*.o

.PHONY=valgrind
valgrind:
	valgrind --leak-check=full ./main 2> valgrind.txt
