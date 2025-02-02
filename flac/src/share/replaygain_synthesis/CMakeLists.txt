add_library(replaygain_synthesis STATIC
    replaygain_synthesis.c)
if(WIN32)
    set_property(TARGET replaygain_analysis PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:${CMAKE_BUILD_TYPE}>:${CMAKE_BUILD_TYPE}>")
endif(WIN32)