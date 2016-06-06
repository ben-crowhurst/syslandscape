set(SOURCES
  AboutHandler.cpp
  HomeHandler.cpp
  )

SET(EXAMPLE_NAME server)
add_executable(${EXAMPLE_NAME} server.cpp ${SOURCES})
target_link_libraries(${EXAMPLE_NAME} -lasan -lubsan)
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_UTIL})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_WEB})
target_link_libraries(${EXAMPLE_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_custom_target(CopyExampleWeb ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/www ${CMAKE_CURRENT_BINARY_DIR}/www)
add_dependencies(${EXAMPLE_NAME} CopyExampleWeb)

SET(EXAMPLE_NAME client)
add_executable(${EXAMPLE_NAME} client.cpp ${SOURCES})
target_link_libraries(${EXAMPLE_NAME} -lasan -lubsan)
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_UTIL})
target_link_libraries(${EXAMPLE_NAME} ${SYSLANDSCAPE_WEB})
target_link_libraries(${EXAMPLE_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
