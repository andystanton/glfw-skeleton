all:
	mkdir -p build;
	cd build && cmake .. && make;

.PHONY : all

clean:
	rm -rf build

.PHONY : clean

runonly:
	pushd build 1>/dev/null && ./bin/glfw-skeleton;

.PHONY : runonly

run: | all runonly

.PHONY : run

testonly:
	pushd build 1>/dev/null && ./bin/glfw-skeleton-unittests --reporter=spec;

.PHONY : testonly

test: | all testonly

.PHONY : test