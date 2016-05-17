SET(project_LIBS libglew_static glfw ${GLFW_LIBRARIES})

SET(project_BIN ${PROJECT_NAME})
SET(project_LIB ${PROJECT_NAME}_lib CACHE INTERNAL "Project Library")

SET(project_SRCS
        Skeleton.cpp
        util/colorhelper.cpp
        util/pathhelper.cpp
        util/shaderhelper.cpp)

ADD_LIBRARY(${project_LIB} ${project_SRCS})

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

ADD_EXECUTABLE(${project_BIN} main.cpp)

SET_TARGET_PROPERTIES(
        ${project_BIN}
        PROPERTIES
        OUTPUT_NAME ${APPLICATION_NAME}
        CXX_STANDARD 14)

SET_TARGET_PROPERTIES(
        ${project_LIB}
        PROPERTIES
        OUTPUT_NAME ${APPLICATION_NAME}
        CXX_STANDARD 14)

INCLUDE_DIRECTORIES(
        ${EASYLOGGINGPP_INCLUDE_PATH}
        ${GLFW_INCLUDE_PATH}
        ${GLEW_INCLUDE_PATH}
        ${GLM_INCLUDE_PATH})

TARGET_LINK_LIBRARIES(${project_LIB} ${project_LIBS})
TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIB} ${project_LIBS})

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES
        OUTPUT_NAME ${project_BIN}
        CLEAN_DIRECT_OUTPUT 1)

ADD_CUSTOM_TARGET("${project_BIN}_copy_resources" ALL
        COMMENT "Copying resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${EXECUTABLE_OUTPUT_PATH}/shaders")

ADD_DEPENDENCIES("${project_BIN}" "${project_BIN}_copy_resources")
