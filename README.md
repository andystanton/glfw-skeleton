# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.png?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton C++11 application that makes use of the [GLFW library](http://www.glfw.org) and [CMake](http://www.cmake.org/) to speed up initial project setup.

The skeleton includes a Bandit unit testing runner as well as support for Google Mock. All libraries are built from source included either as git submodules which are built from source with the project to ensure portability.

![](http://andystanton.github.io/glfw-skeleton/images/content/3.0/glfw-skeleton.png)

## Requirements

* A C++11 compiler
* CMake >= 2.8.8
* Make >= 3.81
* Rake >= 10.3
* OpenGL >= 3.2

## Quick Start

```sh
git clone https://github.com/andystanton/glfw-skeleton.git --recursive && cd glfw-skeleton

rake default start
```

## Libraries

* [glfw](http://www.glfw.org/) 3.0.4
* [glm](https://github.com/g-truc/glm) 0.9.5
* [glew](http://glew.sourceforge.net/) 1.10.0
* [bandit](http://banditcpp.org/) dfb6b7
* [gmock](https://code.google.com/p/googlemock/) & [gtest](https://code.google.com/p/googletest/) 1.7.0
