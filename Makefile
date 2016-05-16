all:
	mkdir -p build;
	cd build && cmake .. && make;

.PHONY : all

clean:
	rm -rf build

.PHONY : clean

runonly:
	cd build/bin && ./glfw-skeleton;

.PHONY : runonly

run: | all runonly

.PHONY : run

testonly:
	cd build/bin && ./glfw-skeleton-unittests --reporter=spec;

.PHONY : testonly

test: | all testonly

.PHONY : test
