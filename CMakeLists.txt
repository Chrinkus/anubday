cmake_minimum_required(VERSION 3.13)

project(bday VERSION 0.1 LANGUAGES C)
enable_testing()

# Compiler settings
set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(source)
