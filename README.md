# glfw-skeleton [![Build Status](http://drone.cyniq.com/api/badge/github.com/andystanton/glfw-skeleton/status.svg?branch=master)](http://drone.cyniq.com/github.com/andystanton/glfw-skeleton)

A skeleton C++14 OpenGL 3.2 app that uses the [GLFW](http://www.glfw.org), [GLEW](http://glew.sourceforge.net/) and [GLM](http://glm.g-truc.net/) libraries and builds with [CMake](http://www.cmake.org/). [Bandit](http://banditcpp.org/) is used for unit testing.

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

* [glfw](http://www.glfw.org/) 3.1.2
* [glm](http://glm.g-truc.net/) 0.9.5
* [glew](http://glew.sourceforge.net/) 1.13.0
* [bandit](http://banditcpp.org/) ffa30f3
* [gmock](https://code.google.com/p/googlemock/) & [gtest](https://code.google.com/p/googletest/) 1.7.0
