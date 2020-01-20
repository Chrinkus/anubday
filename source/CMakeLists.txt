add_executable(dbtest sqlite_test.c)
target_link_libraries(dbtest PRIVATE sqlite3)
