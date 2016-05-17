all: | test

.PHONY : test

clean:
	rm -rf build

.PHONY : clean

build:
	mkdir -p build;
	cd build && cmake .. && make;

.PHONY : build

testonly:
	build/testbin/glfw-skeleton-unittests --reporter=spec;

.PHONY : testonly

test: | build testonly

.PHONY : test

runonly:
	build/bin/glfw-skeleton;

.PHONY : runonly

run: | all runonly

.PHONY : run
