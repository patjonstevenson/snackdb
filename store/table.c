#include "table.h"

#include <stdlib.h>
#include <stdio.h>


Table* new_table() {
    Table* table = malloc(sizeof(Table));

    table->num_rows = 0;

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }

    return table;
}

void free_table(Table* table) {
    for (int i = 0; table->pages[i]; i++) {
        free(table->pages[i]);
    }

    free(table);
}


/*
 * This function helps us determine where to read/write in memory for a
 * particular row. Returns a pointer to the location in memory.
 */
void* row_slot(Table* table, uint32_t row_num) {
    // Determine page where row is located
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];
    printf("row_num: %d\n", sizeof(row_num));
    printf("page_num: %d\n", page_num);

    if (page == NULL) {
        // Allocate memory only when we try to access page
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }

    // Find row within the page
    // TODO: This is broken. Can't figure out why. Is it a typing issue?
    uint32_t row_offset = row_num % (uint32_t)ROWS_PER_PAGE;
    printf("ROWS_PER_PAGE: %d\n", sizeof(ROWS_PER_PAGE));
    printf("Row offset: %d\n", row_offset);
    printf("row_num & ROWS_PER_PAGE: %d\n", row_num % ROWS_PER_PAGE);

    // Find row within memory
    uint32_t byte_offset = row_offset * ROW_SIZE;
    printf("Byte offset: %d\n", byte_offset);
    
    printf("Row slot: %p\n", page + byte_offset);

    return page + byte_offset;
}

