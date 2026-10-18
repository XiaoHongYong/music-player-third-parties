add_library(replaygain_analysis STATIC
    replaygain_analysis.c)
if(WIN32)
    set_property(TARGET replaygain_analysis PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(WIN32)