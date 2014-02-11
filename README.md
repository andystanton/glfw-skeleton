# glfw-skeleton [![Build Status](https://travis-ci.org/andystanton/glfw-skeleton.png?branch=master)](https://travis-ci.org/andystanton/glfw-skeleton)

A skeleton c++ application making use of the [GLFW library](http://www.glfw.org) to speed up initial project setup.

Project files for various IDEs can be generated using cmake's -G switch.

![](http://andystanton.github.io/assets/images/readme.md/glfw-skeleton/glfw-skeleton.png)

## Requirements

* [cmake](http://www.cmake.org/cmake/resources/software.html) >= 2.8

## Usage

Run the following commands to generate the makefile and build the project.

```
cmake .
make
```

This will create the glfw-skeleton executable in the project directory.

## Generating project files for your IDE

Run the following command to generate the project files for your IDE:

```
cmake . -G {ide_name}
```

For more information on cmake's project generators see their [documentation](http://www.cmake.org/Wiki/CMake_Generator_Specific_Information).


