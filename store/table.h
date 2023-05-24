#ifndef TABLE_H
#define TABLE_H

#include "row.h"

#include <stdint.h>


#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096
#define ROWS_PER_PAGE  PAGE_SIZE / ROW_SIZE
#define TABLE_MAX_ROWS ROWS_PER_PAGE * TABLE_MAX_PAGES


typedef struct {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;

// Function to determine where to read/write in memory for a particular row
void* row_slot(Table* table, uint32_t row_num);


#endif
