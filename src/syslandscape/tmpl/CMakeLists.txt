set(SOURCES
  TemplateException.cpp
  Data.cpp
  Token.cpp TokenText.cpp TokenVariable.cpp TokenEnd.cpp TokenIf.cpp
  TokenFor.cpp TokenInclude.cpp 
  Template.cpp
  Storage.cpp  DirectoryStorage.cpp StringStorage.cpp
  Engine.cpp
  )

add_library(${SYSLANDSCAPE_TMPL} SHARED ${SOURCES})
if (test)
  target_link_libraries(${SYSLANDSCAPE_TMPL} -lasan -lubsan)
endif()
target_link_libraries(${SYSLANDSCAPE_TMPL} ${SYSLANDSCAPE_UTIL})
target_link_libraries(${SYSLANDSCAPE_TMPL} ${Boost_LIBRARIES})
