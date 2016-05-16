SET(project_LIBS libglew_static glfw ${GLFW_LIBRARIES})

SET(project_BIN ${PROJECT_NAME})

SET(project_SRCS
        main.cpp
        Skeleton.cpp
        util/cli/CLIParser.cpp
        util/cli/Configuration.cpp
        util/log/Logger.cpp
        util/log/LoggerFactory.cpp
        util/colourhelper.cpp
        util/pathhelper.cpp
        util/shaderhelper.cpp)

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})

SET_TARGET_PROPERTIES(
        ${project_BIN}
        PROPERTIES
        OUTPUT_NAME ${APPLICATION_NAME}
        CXX_STANDARD 14)

INCLUDE_DIRECTORIES(
        ${GLFW_INCLUDE_PATH}
        ${GLEW_INCLUDE_PATH}
        ${GLM_INCLUDE_PATH})

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

ADD_CUSTOM_TARGET("${project_BIN}_copy_resources" ALL
        COMMENT "Copying resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${EXECUTABLE_OUTPUT_PATH}/shaders")

ADD_DEPENDENCIES("${project_BIN}" "${project_BIN}_copy_resources")
