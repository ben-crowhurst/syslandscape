
SET(TEST_NAME test-tmpl-data)
add_executable(${TEST_NAME} data.cpp)
target_link_libraries(${TEST_NAME} -lasan -lubsan)
target_link_libraries(${TEST_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_NAME} gtest gtest_main)
add_test(${TEST_NAME} ${TEST_NAME})

SET(TEST_NAME test-tmpl-token)
add_executable(${TEST_NAME} token.cpp)
target_link_libraries(${TEST_NAME} -lasan -lubsan)
target_link_libraries(${TEST_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_NAME} gtest gtest_main)
add_test(${TEST_NAME} ${TEST_NAME})

SET(TEST_NAME test-tmpl-template)
add_executable(${TEST_NAME} template.cpp)
target_link_libraries(${TEST_NAME} -lasan -lubsan)
target_link_libraries(${TEST_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_NAME} gtest gtest_main)
add_test(${TEST_NAME} ${TEST_NAME})

# Template directory
add_custom_target(CopyTemplate ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/template ${CMAKE_CURRENT_BINARY_DIR})

set(TEST_NAME test-tmpl-directorystorage)
add_executable(${TEST_NAME} directorystorage.cpp)
target_link_libraries(${TEST_NAME} -lasan -lubsan)
target_link_libraries(${TEST_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${TEST_NAME} ${SYSLANDSCAPE})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_NAME} gtest gtest_main)
add_test(
  ${TEST_NAME}
  ${TEST_NAME}
  )
add_dependencies(${TEST_NAME} CopyTemplate)
