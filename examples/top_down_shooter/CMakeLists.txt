add_executable(top_down_shooter
    client.c
    )

target_link_libraries(top_down_shooter
    LINK_PUBLIC
    c2ge)
