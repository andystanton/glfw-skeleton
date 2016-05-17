SET(test_LIBS gtest gtest_main libglew_static glfw ${GLFW_LIBRARIES})

SET(test_BIN ${PROJECT_NAME}-unittests)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/testbin")

INCLUDE_DIRECTORIES(
        ${EASYLOGGINGPP_INCLUDE_PATH}
        ${GTEST_INCLUDE_PATH}
        ${BANDIT_INCLUDE_PATH}
        ${GLFW_INCLUDE_PATH}
        ${GLEW_INCLUDE_PATH}
        ${GLM_INCLUDE_PATH})

SET(test_SRCS
        banditrunner.cpp
        specs/util/colorhelperSpec.cpp
        specs/util/shaderhelperSpec.cpp)

ADD_EXECUTABLE(${test_BIN} ${test_SRCS})

SET_TARGET_PROPERTIES(
        ${test_BIN}
        PROPERTIES
        CXX_STANDARD 14)

TARGET_LINK_LIBRARIES(${test_BIN} glfw-skeleton_lib ${test_LIBS})

ADD_TEST(${test_BIN} ${EXECUTABLE_OUTPUT_PATH}/${test_BIN} --reporter=spec)

ADD_CUSTOM_TARGET("${test_BIN}_copy_resources" ALL
        COMMENT "Copying test resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/fixtures" "${EXECUTABLE_OUTPUT_PATH}/fixtures")

ADD_DEPENDENCIES("${test_BIN}" "${test_BIN}_copy_resources")
