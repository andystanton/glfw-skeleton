cmake_minimum_required(VERSION 3.21)
project(glfw-skeleton
    VERSION 1.0.0
    DESCRIPTION "A skeleton C++20 OpenGL 4.1 application"
    LANGUAGES C CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE)

set(GLAD_GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/glad")

if(EXISTS "${GLAD_GENERATED_DIR}/include/glad/gl.h")
    message(STATUS "Using pre-generated glad files from ${GLAD_GENERATED_DIR}")
    add_library(glad STATIC
        ${GLAD_GENERATED_DIR}/src/gl.c
        ${GLAD_GENERATED_DIR}/include/glad/gl.h
        ${GLAD_GENERATED_DIR}/include/KHR/khrplatform.h)
    target_include_directories(glad PUBLIC ${GLAD_GENERATED_DIR}/include)
    target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})
else()
    message(STATUS "Pre-generated glad files not found, will generate at build time")
    message(STATUS "This requires: brew install jinja2-cli (or python3 -m pip install jinja2)")

    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE)

    FetchContent_GetProperties(glad)
    if(NOT glad_POPULATED)
        FetchContent_Populate(glad)
        add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
    endif()

    glad_add_library(glad REPRODUCIBLE API gl:core=4.1)
endif()

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(glfw glm)

set(PROJECT_SOURCES
    src/app.cpp
    src/GLContext.cpp
    src/Skeleton.cpp
    src/util/colorhelper.cpp
    src/util/pathhelper.cpp
    src/util/shaderhelper.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
        glm::glm)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMENT "Copying shaders to build directory"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
    VERBATIM)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wpedantic)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
