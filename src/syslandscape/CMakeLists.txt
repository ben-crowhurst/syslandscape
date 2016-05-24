set(SOURCES
  Exception.cpp
  Environment.cpp
  )

add_library(syslandscape SHARED ${SOURCES})
target_link_libraries(syslandscape -lasan -lubsan)
target_link_libraries(syslandscape ${Boost_LIBRARIES})
target_link_libraries(syslandscape ${CMAKE_THREAD_LIBS_INIT})
