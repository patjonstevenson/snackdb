add_library(repl
    input_buffer.c
    metacommand.c
    statement.c
)

target_include_directories(repl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(repl LINK_PUBLIC store)

