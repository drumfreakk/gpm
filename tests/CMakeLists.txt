include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(TEST_SOURCES
	check_gpm.c
	check_jsmn.c
	check_funcs.c
)

set(TEST_HEADERS
	check_gpm.h
	${SRC}/jsmn/jsmn.h
	${SRC}/funcs.h
)

add_executable(check_gpm ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(check_gpm jsmn ${CHECK_LIBRARIES})
