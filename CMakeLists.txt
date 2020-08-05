cmake_minimum_required(VERSION 3.10)

project(gpm)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


set(USER_AGENT "kippenjongen-gpm")
configure_file(gpmConfig.h.in gpmConfig.h)


set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 

add_subdirectory(jcon)

add_executable(gpm main.c)

include_directories(${CURL_INCLUDE_DIR})
list(APPEND LIBS ${CURL_LIBRARIES})

list(APPEND LIBS jcon)

target_link_libraries(gpm PUBLIC ${LIBS})
target_include_directories(gpm PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS gpm DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/gpmConfig.h" DESTINATION include)
