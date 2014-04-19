cmake_minimum_required(VERSION 2.8)
project(glfw-skeleton)

set(glfw-skeleton_VERSION_MAJOR 1)
set(glfw-skeleton_VERSION_MINOR 0)

# glfw-skeleton
add_executable(glfw-skeleton src/main.cpp)

# enable testing - not currently in use but required for 'make test' that travis-ci runs.
enable_testing()

# disable unnecessary glfw targets
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

# glfw
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)
target_link_libraries(glfw-skeleton glfw ${GLFW_LIBRARIES})
target_link_libraries(glfw-skeleton glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})


