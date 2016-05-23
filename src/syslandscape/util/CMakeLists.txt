set(SOURCES
  Base64.cpp
  StringUtil.cpp
  )

add_library(syslandscape-util SHARED ${SOURCES})
target_link_libraries(syslandscape-util -lasan -lubsan)
target_link_libraries(syslandscape-util ${Boost_LIBRARIES})
target_link_libraries(syslandscape-util ${CMAKE_THREAD_LIBS_INIT})
