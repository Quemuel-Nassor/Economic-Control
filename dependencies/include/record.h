/*
 * This library contains a definition of the data type of the "rec" and methods to manipulate
 * dinamic lists of him
 *
 * Author: Quemuel Alves Nassor
 * Date: 01/05/21
 */

#ifndef RECORD_H
#define RECORD_H

#include "date_time.h"

/* Max sizes constants */
enum sizes
{
    MAX_DESCRIPTION = 100,
    MAX_DETAILS = 300,
};

/* Record data structure */
typedef struct record
{
    struct record* prev;
    struct record* next;
    size_t id;
    char description[MAX_DESCRIPTION];
    size_t category_id;
    char details[MAX_DETAILS];
    DateTime datetime;
    double value;
    void (*add)(struct record* list, struct record* newItem);
    void (*show)(struct record* item);
} record;

void show_record(record* item);
record* navigate_to_end(record* list);
record* navigate_to_start(record* list);
record* add_start(record* list, record* newItem);
record* add_middle(record* list, record* newItem);
void add_end(record* list, record* newItem);
record* remove_start(record* list);
record* remove_middle(record* list);
void remove_end(record* list);
void clean_list(record* list);
char *serialize_to_json(record *list);
record* new_record(void);
record* new_record_overloaded(size_t id, double value, DateTime datetime, char* description, size_t category_id, char* details);

#endif