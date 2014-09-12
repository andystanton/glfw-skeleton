# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.png?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton C++11 OpenGL 3.2 app that uses the [GLFW](http://www.glfw.org), [GLEW](http://glew.sourceforge.net/) and [GLM](http://glm.g-truc.net/) libraries and builds with [CMake](http://www.cmake.org/). [Bandit](http://banditcpp.org/) is used for unit testing.

All libraries are included as git submodules and built from source with the application to ensure portability.

![](http://andystanton.github.io/glfw-skeleton/images/content/3.0.1/glfw-skeleton.png)

## Requirements

* A C++11 compiler
* CMake >= 2.8.8
* Make >= 3.81
* Rake >= 10.3
* OpenGL >= 3.2

## Quick Start

```sh
git clone https://github.com/andystanton/glfw-skeleton.git --recursive

cd glfw-skeleton

rake default start
```

## Libraries

* [glfw](http://www.glfw.org/) 3.0.4
* [glm](http://glm.g-truc.net/) 0.9.5
* [glew](http://glew.sourceforge.net/) 1.10.0
* [bandit](http://banditcpp.org/) ffa30f3
* [gmock](https://code.google.com/p/googlemock/) & [gtest](https://code.google.com/p/googletest/) 1.7.0
