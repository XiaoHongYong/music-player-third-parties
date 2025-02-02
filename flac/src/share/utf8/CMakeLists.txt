cmake_minimum_required(VERSION 3.12)

add_library(utf8 STATIC
    charset.c
    iconvert.c
    utf8.c)

if(WIN32)
    set_property(TARGET utf8 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:${CMAKE_BUILD_TYPE}>:${CMAKE_BUILD_TYPE}>")
endif(WIN32)
target_link_libraries(utf8 PUBLIC grabbag)
