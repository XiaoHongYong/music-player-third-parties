add_library(grabbag STATIC
    alloc.c
    cuesheet.c
    file.c
    picture.c
    replaygain.c
    seektable.c
    snprintf.c)
if(WIN32)
    set_property(TARGET grabbag PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(WIN32)
target_link_libraries(grabbag PUBLIC
    FLAC
    replaygain_analysis)
if(TARGET win_utf8_io)
    target_link_libraries(grabbag PUBLIC win_utf8_io)
endif()
