FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_LIBS gtest gtest_main gmock gmock_main glfw ${GLFW_LIBRARIES} libglew_static)
SET (test_BIN ${PROJECT_NAME}-unittests)

include_directories(${GMOCK_INCLUDE_PATH}
                    ${GTEST_INCLUDE_PATH}
                    ${BANDIT_INCLUDE_PATH}
                    ${GLFW_INCLUDE_PATH}
                    ${GLEW_INCLUDE_PATH})

# message("Output sources")
# foreach(source ${ALL_SRCS})
#     message(${source})
# endforeach()

ADD_EXECUTABLE(${test_BIN} ${test_SRCS} ${ALL_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})



ADD_TEST(${test_BIN} ${EXECUTABLE_OUTPUT_PATH}/${test_BIN} --reporter=spec)
