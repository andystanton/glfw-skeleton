SET(test_LIBS gtest gtest_main libglew_static glfw ${GLFW_LIBRARIES})

SET(test_BIN ${PROJECT_NAME}-unittests)

INCLUDE_DIRECTORIES(
        ${EASYLOGGINGPP_INCLUDE_PATH}
        ${GTEST_INCLUDE_PATH}
        ${BANDIT_INCLUDE_PATH}
        ${GLFW_INCLUDE_PATH}
        ${GLEW_INCLUDE_PATH}
        ${GLM_INCLUDE_PATH})

#SET(project_SRCS
#        ../src/Skeleton.cpp
#        ../src/util/cli/CLIParser.cpp
#        ../src/util/cli/Configuration.cpp
#        ../src/util/log/Logger.cpp
#        ../src/util/log/LoggerFactory.cpp
#        ../src/util/colorhelper.cpp
#        ../src/util/pathhelper.cpp
#        ../src/util/shaderhelper.cpp)

SET(test_SRCS
        banditrunner.cpp
        specs/util/cli/CLIParserSpec.cpp
        specs/util/cli/ConfigurationSpec.cpp
        specs/util/colorhelperSpec.cpp)

ADD_EXECUTABLE(${test_BIN} ${test_SRCS})

SET_TARGET_PROPERTIES(
        ${test_BIN}
        PROPERTIES
        CXX_STANDARD 14)

MESSAGE(STATUS "foo ${project_LIB}")

TARGET_LINK_LIBRARIES(${test_BIN} glfw-skeleton_lib ${test_LIBS})

ADD_TEST(${test_BIN} ${EXECUTABLE_OUTPUT_PATH}/${test_BIN} --reporter=spec)
