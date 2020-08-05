add_library(jcon jcon.c)
target_include_directories(jcon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS jcon DESTINATION lib)
install(FILES jcon.h DESTINATION include)

