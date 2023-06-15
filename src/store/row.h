#ifndef ROW_H
#define ROW_H

#include <stdint.h>


/*
 * Macros
 */
#define COLUMN_USERNAME_SIZE (32u)
#define COLUMN_EMAIL_SIZE (255u)
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)


/*
 * Types
 */
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;


/*
 * Compact Representation of Row
 */
extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;

/*
 * Function Declaration
 */
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);

#endif
