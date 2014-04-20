# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.png?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton C++11 application that makes use of the [GLFW library](http://www.glfw.org) and [CMake](http://www.cmake.org/) to speed up initial project setup.

The skeleton includes a Bandit unit testing runner as well as support for Google Mock. All libraries are built from source included either as git submodules or bundled where this is not possible (e.g. GMock) to ensure portability.

![](http://andystanton.github.io/glfw-skeleton/images/content/2.0/glfw-skeleton.png)

## Requirements

* A C++11 compiler
* [CMake >= 2.8](http://www.cmake.org/cmake/resources/software.html)

## Libraries

* [GLFW](http://www.glfw.org/) 3.0.4
* [GMock](https://code.google.com/p/googlemock/) & [GTest](https://code.google.com/p/googletest/) 1.7.0
* [Bandit](http://banditcpp.org/) 1.1.4

## Quick Start

Clone the project:

```sh
git clone https://github.com/andystanton/glfw-skeleton.git --recursive && cd glfw-skeleton
```

Run the following commands to generate the makefile and build:

```sh
./configure
./compile
```

This will create the glfw-skeleton executable in the project directory.

## Generating project files for your IDE

Run the following command to generate the project files for your IDE:

```sh
cmake . -G {ide_name}
```

Note that if you have already build the makefile, you'll need to delete the CMakeCache.txt file. For convenience you can run ```./clean``` which will clean all generated files from the project.

For more information on CMake's project generators and a full list of supported platforms and IDEs, see the [documentation](http://www.cmake.org/Wiki/CMake_Generator_Specific_Information).
