cmake_minimum_required(VERSION 3.15...3.28)

PROJECT(agg)

include_directories(
    ${PROJECT_SOURCE_DIR}/include()
)

set(SRC 
    ${PROJECT_SOURCE_DIR}/src/agg_arc.cpp
    ${PROJECT_SOURCE_DIR}/src/agg_image_filters.cpp
    ${PROJECT_SOURCE_DIR}/src/agg_rounded_rect.cpp
    ${PROJECT_SOURCE_DIR}/src/agg_vcgen_stroke.cpp
)

add_library(${PROJECT_NAME}_STATIC ${SRC})
if(WIN32)
    set_property(TARGET ${PROJECT_NAME}_STATIC PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:${CMAKE_BUILD_TYPE}>:${CMAKE_BUILD_TYPE}>")
endif(WIN32)
