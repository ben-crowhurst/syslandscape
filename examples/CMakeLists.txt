add_definitions(-fsanitize=address -fsanitize=leak)
#add_subdirectory(web)

SET(EXAMPLE_NAME server)
add_executable(${EXAMPLE_NAME} web/server1.cpp)
target_link_libraries(${EXAMPLE_NAME} -lasan -lubsan)
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_UTIL})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_WEB})
target_link_libraries(${EXAMPLE_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

