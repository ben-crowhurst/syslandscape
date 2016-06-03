set(SOURCES
  HTTPMethod.cpp HTTPStatus.cpp
  HTTPRequestParser.cpp
  HTTPHandler.cpp
  HTTPResponse.cpp
  HTTPRequest.cpp
  HTTPConnection.cpp
  HTTPConnectionManager.cpp
  HTTPServer.cpp
  HTTPTokens.cpp
  HTTPCookie.cpp
  WebException.cpp
  WebHandler.cpp
  WebHandlerFactory.cpp
  WebContext.cpp
  WebPathSegment.cpp
  http_parser.c

  Types.cpp
  Headers.cpp
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
