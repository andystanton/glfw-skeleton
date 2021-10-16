.PHONY : build clean runonly run

all: | build

clean:
	@rm -rf cmake-build-debug

build:
	@mkdir -p cmake-build-debug
	@cd cmake-build-debug && cmake .. && make

runonly:
	@cmake-build-debug/bin/glfw-skeleton

run: | all runonly
