cmake_minimum_required(VERSION 3.10)

project(gpm)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


set(USER_AGENT "kippenjongen-gpm")
configure_file(config.h.in config.h)


set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 

add_executable(gpm main.c)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(gpm ${CURL_LIBRARIES})


target_include_directories(gpm PUBLIC "${PROJECT_BINARY_DIR}")
