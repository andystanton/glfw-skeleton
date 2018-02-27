#
# Project Properties
#
cmake_minimum_required(VERSION 3.7)
PROJECT(glfw-skeleton)

include(ExternalProject)
find_package (OpenGL REQUIRED)
set(CMAKE_CXX_STANDARD 17)
SET(APPLICATION_NAME "GLFW Skeleton")
SET(APPLICATION_CODENAME "${PROJECT_NAME}")
SET(APPLICATION_COPYRIGHT_YEARS "2014-2018")
SET(APPLICATION_VERSION_MAJOR 5)
SET(APPLICATION_VERSION_MINOR 0)
SET(APPLICATION_VERSION_PATCH 0)
SET(APPLICATION_VERSION_TYPE "RELEASE")
SET(APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET(APPLICATION_ID "${PROJECT_NAME}")

#
# Project Output Paths
#
SET(MAINFOLDER ${PROJECT_SOURCE_DIR})
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

#
# Project Search Paths
#
LIST(APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# glfw
#
OPTION(GLFW_BUILD_EXAMPLES  "Build the GLFW example programs"   OFF)
OPTION(GLFW_BUILD_TESTS     "Build the GLFW test programs"      OFF)
OPTION(GLFW_BUILD_DOCS      "Build the GLFW documentation"      OFF)
OPTION(GLFW_INSTALL         "Generate installation target"      OFF)

ADD_SUBDIRECTORY(lib/glfw)

SET(GLFW_INCLUDE_PATH "${MAINFOLDER}/lib/glfw/include")

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

SET(GLEW_INCLUDE_PATH "${CMAKE_BINARY_DIR}/include")

#
# glm
#
SET(GLM_INCLUDE_PATH "${MAINFOLDER}/lib/glm")
MESSAGE("FOO ${CMAKE_BINARY_DIR}/lib/libGLEW.a")
SET(project_LIBS ${OPENGL_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libGLEW.a glfw ${GLFW_LIBRARIES})

SET(project_BIN ${PROJECT_NAME})

SET(
    project_SRCS
    src/main.cpp
    src/Skeleton.cpp
    src/util/colorhelper.cpp
    src/util/pathhelper.cpp
    src/util/shaderhelper.cpp
)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})

SET_TARGET_PROPERTIES(
    ${project_BIN}
    PROPERTIES
    OUTPUT_NAME ${APPLICATION_NAME}
    CXX_STANDARD 17)

INCLUDE_DIRECTORIES(
    ${GLFW_INCLUDE_PATH}
    ${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_PATH})

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES
    OUTPUT_NAME ${project_BIN}
    CLEAN_DIRECT_OUTPUT 1)

add_custom_target(
    glfw-copy-shaders ALL
    COMMENT "Copying shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders ${EXECUTABLE_OUTPUT_PATH}/shaders
)

ADD_DEPENDENCIES("${project_BIN}" glew glfw-copy-shaders)
