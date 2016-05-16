# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.svg?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton C++14 OpenGL 4.1 app that uses the [GLFW](http://www.glfw.org), [GLEW](http://glew.sourceforge.net/) and [GLM](http://glm.g-truc.net/) libraries and builds with [CMake](http://www.cmake.org/). [Bandit](http://banditcpp.org/) is used for unit testing.

All libraries are included as git submodules and built from source with the application to ensure portability.

![](http://andystanton.github.io/glfw-skeleton/images/content/3.0.1/glfw-skeleton.png)

## Requirements

* A C++14 compiler
* CMake >= 2.8.12
* Make >= 3.81
* OpenGL >= 4.1

## Quick Start

```sh
git clone https://github.com/andystanton/glfw-skeleton.git --recursive

cd glfw-skeleton

make test run
```

## Libraries

* [glfw](http://www.glfw.org/)
* [glm](http://glm.g-truc.net/)
* [glew](http://glew.sourceforge.net/)
* [bandit](http://banditcpp.org/)
* [googletest](https://github.com/google/googletest)
