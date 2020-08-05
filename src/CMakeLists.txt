set(LIB_SOURCES
  jcon/jcon.c
)

set(MAIN_SOURCES
  main.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  jcon/jcon.h
)

add_library(jcon STATIC ${LIB_SOURCES} ${HEADERS})

set(USER_AGENT "kippenjongen-gpm")
configure_file(gpmConfig.h.in gpmConfig.h)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 


add_executable(gpm ${HEADERS} ${MAIN_SOURCES})

list(APPEND LIBS ${CURL_LIBRARIES})
list(APPEND LIBS jcon)

target_link_libraries(gpm PUBLIC ${LIBS})

install(TARGETS gpm DESTINATION bin)
install(TARGETS jcon
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/jcon/jcon.h DESTINATION include)
install(FILES "${PROJECT_BINARY_DIR}/gpmConfig.h" DESTINATION include)
