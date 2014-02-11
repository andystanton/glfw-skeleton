cmake_minimum_required(VERSION 2.8)
project(glfw-skeleton)

set(glfw-skeleton_VERSION_MAJOR 1)
set(glfw-skeleton_VERSION_MINOR 0)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(glfw-skeleton src/main.cpp)

add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)
target_link_libraries(glfw-skeleton glfw ${GLFW_LIBRARIES})
target_link_libraries(glfw-skeleton glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

