include_directories("${PROJECT_SOURCE_DIR}/source")

add_executable(tests_all tests_main.c)
target_link_libraries(tests_all PRIVATE cmocka parse_command)
