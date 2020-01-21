add_library(parse_command parse_command.c)

add_executable(anubday main.c)
target_link_libraries(anubday PRIVATE parse_command)

