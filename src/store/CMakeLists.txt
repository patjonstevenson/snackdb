add_library(store
    row.c
    table.c
)

target_include_libraries(store PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


