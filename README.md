# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.svg?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton C++17 OpenGL 4.1 app that uses the [GLFW](http://www.glfw.org), [GLEW](http://glew.sourceforge.net/) and [GLM](http://glm.g-truc.net/) libraries and builds with [CMake](http://www.cmake.org/).

All libraries are included as git submodules or CMake ExternalProjects and built from source with the application to ensure portability.

![](http://andystanton.github.io/glfw-skeleton/images/content/4.0/glfw-skeleton.png)

## Requirements

* A C++17 compiler
* CMake >= 3.7
* Make >= 3.81
* OpenGL >= 4.1

## Quick Start

```sh
git clone https://github.com/andystanton/glfw-skeleton.git --recursive

cd glfw-skeleton

make run
```

## Libraries

* [glfw](http://www.glfw.org/)
* [glm](http://glm.g-truc.net/)
* [glew](http://glew.sourceforge.net/)
