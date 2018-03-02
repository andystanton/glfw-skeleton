cmake_minimum_required(VERSION 3.7)
PROJECT(glfw-skeleton)

include(ExternalProject)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#
# glfw
#
option(GLFW_BUILD_EXAMPLES  "Build the GLFW example programs"   OFF)
option(GLFW_BUILD_TESTS     "Build the GLFW test programs"      OFF)
option(GLFW_BUILD_DOCS      "Build the GLFW documentation"      OFF)
option(GLFW_INSTALL         "Generate installation target"      OFF)

add_subdirectory(lib/glfw)
set(GLFW_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/lib/glfw/include)
set(GLEW_LIB ${CMAKE_BINARY_DIR}/lib/libGLEW.a)

#
# glew
#
ExternalProject_Add(
    glew
    PREFIX lib/glew
    URL https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.tgz
    URL_HASH SHA256=04de91e7e6763039bc11940095cd9c7f880baba82196a7765f727ac05a993c95
    TLS_VERIFY true
    SOURCE_SUBDIR build/cmake
    BINARY_DIR lib/glew
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=../../ -DBUILD_UTILS=OFF -DBUILD_SHARED_LIBS=OFF
)

set(GLEW_INCLUDE_PATH ${CMAKE_BINARY_DIR}/lib/glew/src/glew/include)
set(GLEW_LIB ${CMAKE_BINARY_DIR}/lib/libGLEW.a)

#
# glm
#
set(GLM_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/lib/glm)

#
# glfw-skeleton
#
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GLFW_INCLUDE_PATH}
    ${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_PATH}
)

set(
    project_SRCS
    src/main.cpp
    src/Skeleton.cpp
    src/util/colorhelper.cpp
    src/util/pathhelper.cpp
    src/util/shaderhelper.cpp
)

add_executable(${PROJECT_NAME} ${project_SRCS})

add_custom_target(
    glfw-copy-shaders ALL
    COMMENT "Copying shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders
)

add_dependencies(${PROJECT_NAME} glew glfw-copy-shaders)
target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIB}
    glfw
)
