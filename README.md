# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.png?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton C++ application that makes use of the [GLFW library](http://www.glfw.org) and [CMake](http://www.cmake.org/) to speed up initial project setup.

![](http://andystanton.github.io/glfw-skeleton/images/content/2.0/glfw-skeleton.png)

## Requirements

* A C++ compiler
* [CMake >= 2.8](http://www.cmake.org/cmake/resources/software.html)

## Quick Start

Clone the project:

```sh
git clone https://github.com/andystanton/glfw-skeleton.git --recursive && cd glfw-skeleton
```

Run the following commands to generate the makefile and build:

```sh
./configure
make
```

This will create the glfw-skeleton executable in the project directory.

## Generating project files for your IDE

Run the following command to generate the project files for your IDE:

```sh
cmake . -G {ide_name}
```

For more information on CMake's project generators and a full list of supported platforms and IDEs, see the [documentation](http://www.cmake.org/Wiki/CMake_Generator_Specific_Information).
