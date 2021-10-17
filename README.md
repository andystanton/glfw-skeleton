# glfw-skeleton [![Build](https://github.com/andystanton/glfw-skeleton/actions/workflows/build.yml/badge.svg)](https://github.com/andystanton/glfw-skeleton/actions/workflows/build.yml)

A skeleton C++20 OpenGL 4.1 app that uses [glfw](http://www.glfw.org), [glad](https://glad.dav1d.de), and [glm](http://glm.g-truc.net) libraries and builds with [CMake](http://www.cmake.org/) so you can start hacking rapidly on OpenGL.

All libraries are retrieved and built using CMake's FetchContent capability to ensure portability.

![](http://andystanton.github.io/glfw-skeleton/images/content/4.0/glfw-skeleton.png)

## Requirements

- C++20
- OpenGL 4.1
- CMake 3.20
- Make (MacOS/Linux)
- Visual Studio 2019 (Windows)

## Quick Start

### MacOS

```sh
git clone https://github.com/andystanton/glfw-skeleton.git
cd glfw-skeleton
make run
```

### Windows

- Clone the repository.
- Open the folder and switch to CMake Targets View as described in [CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio).
- Right click on the `glfw-skeleton` target and choose Debug.

