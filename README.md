# glfw-skeleton [![Build](https://github.com/andystanton/glfw-skeleton/actions/workflows/build.yml/badge.svg)](https://github.com/andystanton/glfw-skeleton/actions/workflows/build.yml)

A skeleton C++20 OpenGL 4.1 app that uses [glfw](http://www.glfw.org), [glad](https://glad.dav1d.de), and [glm](http://glm.g-truc.net) libraries and builds with [CMake](http://www.cmake.org/) to enable rapid cross-platform hacking with OpenGL.

All libraries are retrieved and built using CMake's FetchContent capability to ensure portability.

<img src="docs/images/content/5.0/glfw-skeleton.png" width="700"/>

## Requirements

- C++20
- OpenGL 4.1
- CMake 3.16
- Make (macOS/Linux)
- Visual Studio 2019 (Windows)

## Quick Start

### macOS and Linux

```sh
git clone https://github.com/andystanton/glfw-skeleton.git
cd glfw-skeleton
make run
```

### Windows

- Clone the repository.
- Open the folder in Visual Studio and switch to CMake Targets View as described in [CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio).
- Right click on the `glfw-skeleton` target and choose Debug.

## Compatibility

Tested on macOS 11.6, Windows 10, & Ubuntu 20.04.

| macOS   | Windows | Linux |
| ------- | ------- | ----- |
| <img src="docs/images/content/5.0/macos.png" width="256"/> | <img src="docs/images/content/5.0/windows.png" width="256"/> | <img src="docs/images/content/5.0/linux.png" width="256"/> |

