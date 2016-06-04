set(SOURCES
  WebException.cpp
  http_parser.c

  Types.cpp
  Headers.cpp
  Cookie.cpp
  Cookies.cpp
  Request.cpp
  Response.cpp
  Service.cpp
  Settings.cpp
  Connection.cpp
  internal/IOServicePool.cpp
  internal/ConnectionManager.cpp
  internal/HttpRequestUtil.cpp
  internal/HttpResponseUtil.cpp
  )

add_library(${SYSLANDSCAPE_WEB} SHARED ${SOURCES})
if (test)
  target_link_libraries(${SYSLANDSCAPE_WEB} -lasan -lubsan)
endif()
target_link_libraries(${SYSLANDSCAPE_WEB} ${SYSLANDSCAPE})
target_link_libraries(${SYSLANDSCAPE_WEB} ${SYSLANDSCAPE_UTIL})
target_link_libraries(${SYSLANDSCAPE_WEB} ${SYSLANDSCAPE_TMPL})
target_link_libraries(${SYSLANDSCAPE_WEB} ${Boost_LIBRARIES})
