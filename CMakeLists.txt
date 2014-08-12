#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(glfw-skeleton)
SET(APPLICATION_NAME "GLFW Skeleton")
SET(APPLICATION_CODENAME "${PROJECT_NAME}")
SET(APPLICATION_COPYRIGHT_YEARS "2014")
SET(APPLICATION_VERSION_MAJOR 2)
SET(APPLICATION_VERSION_MINOR 0)
SET(APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET(APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")

#
# Copy directory contents
#
MACRO(COPY_FILES srcDir destDir)
    MESSAGE(STATUS "Copying contents of directory ${srcDir} to ${destDir}")
    MAKE_DIRECTORY(${destDir})

    FILE(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    FOREACH(templateFile ${templateFiles})
        SET(srcTemplatePath ${srcDir}/${templateFile})
        IF(NOT IS_DIRECTORY ${srcTemplatePath})
            MESSAGE(STATUS "Copying file ${templateFile}")
            FILE(COPY ${srcTemplatePath} DESTINATION ${destDir})
        ENDIF(NOT IS_DIRECTORY ${srcTemplatePath})
    ENDFOREACH(templateFile)
ENDMACRO()

#
# Debugging Options
#
SET(CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
SET(MAINFOLDER ${PROJECT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET(LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Project Search Paths
#
LIST(APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# Set compiler warnings
#
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wfloat-equal -Wno-unused-parameter -Wno-unknown-pragmas")

#
# Enable C++11
#
IF(CMAKE_COMPILER_IS_GNUCXX)
    IF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
        MESSAGE(FATAL_ERROR "Compiler does not support C++11")
    ELSE()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ENDIF()
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    ENDIF()
ELSEIF(MSVC)
    # On by default
ELSE()
    MESSAGE(FATAL_ERROR "Compiler not supported")
ENDIF()

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
OPTION(glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
ADD_SUBDIRECTORY(lib/glew)

SET(GLEW_INCLUDE_PATH "${MAINFOLDER}/lib/glew/include")

#
# glm
#
SET(GLM_INCLUDE_PATH "${MAINFOLDER}/lib/glm")

#
# gmock
#
ADD_SUBDIRECTORY(lib/gmock)

SET(GTEST_INCLUDE_PATH "${gtest_SOURCE_DIR}/include")
SET(GMOCK_INCLUDE_PATH "${gmock_SOURCE_DIR}/include")

SET_PROPERTY(TARGET gmock       APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
SET_PROPERTY(TARGET gmock_main  APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
SET_PROPERTY(TARGET gtest       APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
SET_PROPERTY(TARGET gtest_main  APPEND_STRING PROPERTY COMPILE_FLAGS " -w")

#
# Bandit
#
ADD_SUBDIRECTORY(lib/bandit)

SET(BANDIT_INCLUDE_PATH "${MAINFOLDER}/lib/bandit")

#
# Add project sources
#
ADD_SUBDIRECTORY(src)

#
# Add test sources and enable testing
#
ENABLE_TESTING()

ADD_SUBDIRECTORY(test)
