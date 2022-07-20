cmake_minimum_required(VERSION 3.10)

add_executable(top_down_shooter
    client.c
    )

target_link_libraries(top_down_shooter PRIVATE c2ge)
