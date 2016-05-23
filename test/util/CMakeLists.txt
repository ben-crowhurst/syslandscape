
SET(TEST_NAME test-util-base64)
add_executable(${TEST_NAME} base64.cpp)
target_link_libraries(${TEST_NAME} -lasan -lubsan)
target_link_libraries(${TEST_NAME} ${SYSLANDSCAPE_UTIL})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_NAME} gtest gtest_main)
add_test(${TEST_NAME} ${TEST_NAME})
