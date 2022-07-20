cmake_minimum_required(VERSION 3.10)

add_executable(tests
    runner.c
    tests/test_ecs.c
    )

target_link_libraries(tests PRIVATE c2ge)

add_custom_target(test COMMAND tests DEPENDS c2ge)
