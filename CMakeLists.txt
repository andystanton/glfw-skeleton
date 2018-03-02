cmake_minimum_required(VERSION 3.7)
PROJECT(glfw-skeleton)

include(ExternalProject)
find_package (OpenGL REQUIRED)
set(CMAKE_CXX_STANDARD 17)

#
# Project Output Paths
#
set(MAINFOLDER ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

#
# Project Search Paths
#
list(APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
include_directories("${MAINFOLDER}/include")

#
# glfw
#
option(GLFW_BUILD_EXAMPLES  "Build the GLFW example programs"   OFF)
option(GLFW_BUILD_TESTS     "Build the GLFW test programs"      OFF)
option(GLFW_BUILD_DOCS      "Build the GLFW documentation"      OFF)
option(GLFW_INSTALL         "Generate installation target"      OFF)

add_subdirectory(lib/glfw)

set(GLFW_INCLUDE_PATH "${MAINFOLDER}/lib/glfw/include")

#
# glew
#
ExternalProject_Add(
    glew
    PREFIX lib/glew
    URL https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.tgz
    URL_HASH SHA256=04de91e7e6763039bc11940095cd9c7f880baba82196a7765f727ac05a993c95
    TLS_VERIFY true
    SOURCE_SUBDIR "build/cmake"
    BINARY_DIR lib/glew
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=../../ -DBUILD_UTILS=OFF -DBUILD_SHARED_LIBS=OFF
)

#set (prefix ${CMAKE_INSTALL_PREFIX})
#set (exec_prefix ${CMAKE_INSTALL_PREFIX})
#set (libdir ${CMAKE_INSTALL_FULL_LIBDIR})
#set (includedir ${CMAKE_INSTALL_FULL_INCLUDEDIR})

set(GLEW_INCLUDE_PATH "${CMAKE_BINARY_DIR}/lib/glew/src/glew/include")

#
# glm
#
set(GLM_INCLUDE_PATH "${MAINFOLDER}/lib/glm")
set(project_LIBS ${OPENGL_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libGLEW.a glfw ${GLFW_LIBRARIES})

set(project_BIN ${PROJECT_NAME})

set(
    project_SRCS
    src/main.cpp
    src/Skeleton.cpp
    src/util/colorhelper.cpp
    src/util/pathhelper.cpp
    src/util/shaderhelper.cpp
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_executable(${project_BIN} ${project_SRCS})

set_target_properties(
    ${project_BIN} PROPERTIES
    OUTPUT_NAME ${project_BIN}
    CXX_STANDARD 17
)

include_directories(
    ${GLFW_INCLUDE_PATH}
    ${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_PATH}
)

add_dependencies("${project_BIN}" glew glfw-copy-shaders)
target_link_libraries(${project_BIN} ${project_LIBS})

add_custom_target(
    glfw-copy-shaders ALL
    COMMENT "Copying shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders
)


