cmake_minimum_required(VERSION 3.10)

project(c2ge)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(test)
add_subdirectory(examples/top_down_shooter)

add_library(c2ge STATIC
    src/utils.c
    src/id_allocator.c
    src/media.c
    )

target_include_directories(c2ge
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(c2ge PUBLIC SDL2 SDL2_image)
