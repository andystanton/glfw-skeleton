FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_LIBS gtest gtest_main gmock gmock_main glfw ${GLFW_LIBRARIES})
SET (test_BIN ${PROJECT_NAME}-unittests)

include_directories(${GMOCK_INCLUDE_PATH}
                    ${GTEST_INCLUDE_PATH}
                    ${BANDIT_INCLUDE_PATH}
                    ${GLFW_INCLUDE_PATH})

# message("Output sources")
# foreach(source ${ALL_SRCS})
#     message(${source})
# endforeach()

ADD_EXECUTABLE(${test_BIN} ${test_SRCS} ${ALL_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})

ADD_CUSTOM_TARGET(check ALL "${MAINFOLDER}/bin/${test_BIN}" --reporter=spec 
                    DEPENDS ${test_BIN} 
                    COMMENT "Executing unit tests..." VERBATIM 
                    SOURCES ${test_SRCS})
ADD_CUSTOM_TARGET(test "${MAINFOLDER}/bin/${test_BIN}" --reporter=spec
                    DEPENDS ${test_BIN} 
                    COMMENT "Executing unit tests..." VERBATIM 
                    SOURCES ${test_SRCS})
