add_library(replaygain_synthesis STATIC
    replaygain_synthesis.c)
if(WIN32)
    set_property(TARGET replaygain_analysis PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(WIN32)