add_library(libtahoot STATIC tahoot.c)

target_include_directories(libtahoot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})