cmake_minimum_required(VERSION 3.20)
project(glfw-skeleton)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET FALSE)

#
# glfw
#
set(GLFW_BUILD_DOCS FALSE)
set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.4
  GIT_PROGRESS TRUE)

#
# glad
#
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad
  GIT_TAG v0.1.34
  GIT_PROGRESS TRUE)

#
# glm
#
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 0.9.9.8
  GIT_PROGRESS TRUE)

#
# fetch dependencies
#
FetchContent_MakeAvailable(glfw glad glm)

#
# glfw-skeleton
#
set(
    PROJECT_SOURCES
    src/app.cpp
    src/GLContext.cpp
    src/Skeleton.cpp
    src/util/colorhelper.cpp
    src/util/pathhelper.cpp
    src/util/shaderhelper.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_custom_target(
    copy-shaders ALL
    COMMENT "Copying shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/shaders)

add_dependencies(${PROJECT_NAME} glfw glad glm copy-shaders)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)
