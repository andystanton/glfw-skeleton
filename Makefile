.PHONY : build clean runonly run

all: | build

clean:
	rm -rf build

build:
	mkdir -p build;
	cd build && cmake .. && make;

runonly:
	build/bin/glfw-skeleton;

run: | all runonly
