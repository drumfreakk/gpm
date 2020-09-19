add_library(jsmn jsmn.h)
target_include_directories(jsmn INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS jsmn DESTINATION lib)
install(FILES jsmn.h DESTINATION include)
