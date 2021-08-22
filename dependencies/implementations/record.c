/*
 * This library contains a definition of the data type of the "rec" and methods to manipulate
 * dinamic lists of him
 *
 * Author: Quemuel Alves Nassor
 * Date: 01/05/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#include "..\include\record.h"
#include "..\include\string_handler.h"
#elif defined(__unix__)
#include "../include/record.h"
#include "../include/string_handler.h"
#endif

/*
 * Function to display record
 * parameter: item, record to show
 */
void show_record(record* item)
{
    printf("          Id: %li\n", item->id);
    printf("          Date: %s\n", item->datetime.format_string(item->datetime,DATETIME));
    printf("          Category id: %li\n", item->category_id);
    printf("          Description: %s\n", item->description);
    printf("          Value: %.2Lf\n", item->value);
    printf("          Details: %s\n", item->details);
    printf("----------------------------------------------------------------------------------------------------\n");
}

/*
 * Function to get end of list
 * parameter: list, list to iterate
 * return: last element pointer
 */
record* navigate_to_end(record* list)
{
    record* end = list;

    while (end->next != NULL)
    {
        end = end->next;
    }

    return end;
}

/*
 * Function to get start of list
 * parameter: list, list to iterate
 * return: first element pointer
 */
record* navigate_to_start(record* list)
{
    record* start = list;

    while (start->prev != NULL)
    {
        start = start->prev;
    }

    return start;
}

/*
 * Function to add an record on start of list
 * parameter: list, list to iterate and return the first element pointer
 * parameter: new_item, element to add on start of list
 * return: first element pointer
 */
record* add_start(record* list, record* new_item)
{
    list = navigate_to_start(list);

    new_item->prev = list->prev;
    list->prev = new_item;
    new_item->next = list;

    return new_item;
}

/*
 * Function to add on middle of list
 * parameter: list, list to iterate
 * parameter: new_item, element to add on middle of list
 * return: first element pointer
 */
record* add_middle(record* list, record* new_item)
{
    new_item->next = list->next;
    list->next != NULL ? list->next->prev = new_item : 0;
    new_item->prev = list;
    list->next = new_item;

    return navigate_to_start(list);
}

/*
 * Function to add on end of list
 * parameter: list, list to iterate
 * parameter: new_item, element to add on middle of list
 */
void add_end(record* list, record* new_item)
{
    list = navigate_to_end(list);

    new_item->prev = list;
    new_item->next = list->next;
    list->next = new_item;
}

/*
 * Function to remove record of start of list
 * parameter: list, list to iterate
 * return: new first element pointer
 */
record* remove_start(record* list)
{
    list = navigate_to_start(list);

    record* new_start = list->next;

    if (new_start != NULL)
        new_start->prev = list->prev;

    free(list);

    return new_start;
}

/*
 * Function to remove record of middle of list
 * parameter: list, list to iterate
 * return: first element pointer
 */
record* remove_middle(record* list)
{
    record* elem = navigate_to_start(list);

    if (list->prev != NULL && list->next != NULL)
    {
        list->prev->next = list->next;
        list->next->prev = list->prev;

        free(list);
    }

    return navigate_to_start(elem);
}

/*
 * Function to remove record of end of list
 * parameter: list, list to iterate
 */
void remove_end(record* list)
{
    list = navigate_to_end(list);

    if (list->prev != NULL)
        list->prev->next = list->next;

    free(list);
}

/*
 * Function to remove all record of list
 * parameter: list, list to iterate
 */
void clean_list(record* list)
{
    list = list->prev != NULL ? navigate_to_start(list) : list;

    while (list->next != NULL)
    {
        remove_end(list);
    }

    free(list);
}

/*
 * Function to serialize all record of list as json string
 * return: serialized json string
 */
char *serialize_to_json(record *list)
{
    char *json_result = (char*)malloc(sizeof(char)*2);
    strcpy(json_result,"\0");
    record *element = navigate_to_start(list);
        
    for(element; element != NULL; element = element->next)
    {
        int size_id = snprintf( NULL, 0, "%li", element->id ) + 1;
        int size_category = snprintf( NULL, 0, "%li", element->category_id ) + 1;
        int size_value = snprintf( NULL, 0, "%Lf", element->value ) + 1;
        size_t size = DATETIME_MAX_LENGTH + MAX_DESCRIPTION + MAX_DETAILS + size_id + size_category + size_value + strlen(json_result) + 77;
        
        char *id = (char*)malloc(sizeof(char)*size_id);
        char *category = (char*)malloc(sizeof(char)*size_category);
        char *value = (char*)malloc(sizeof(char)*size_value);

        sprintf(id, "%li", element->id);
        id[strlen(id)] = '\0';
        sprintf(category, "%li", element->category_id);
        category[strlen(category)] = '\0';
        sprintf(value, "%Lf", element->value);
        value[strlen(value)] = '\0';
        
        char* aux = json_result;
        json_result = (char*)malloc(sizeof(char)*size);
        strcpy(json_result,aux);

        strcat(json_result,string_join(INDEFINITE_LENGTH,EMPTY_SEPARATOR,
        ( element->prev == NULL ? "[{" : ",{"),
        "\"Id\":",id,
        ",\"Description\":\"",element->description,
        "\",\"Category_id\":",category,
        ",\"Details\":\"",element->details,
        "\",\"Datetime\":\"",element->datetime.format_string(element->datetime,DATABASE_UTC),
        "\",\"Value\":",value,
        (element->next == NULL ? "}]" : "}"),NULL));
    
        free(id);
        free(aux);
        free(value);
        free(category);

    }

    return json_result;
}

/*
 * Default record constructor
 * return: minimally initialized registry
 */
record* new_record(void)
{
    record* empty_rec = (record*)malloc(sizeof(record));
    empty_rec->next = NULL;
    empty_rec->prev = NULL;
    empty_rec->datetime = new_datetime();
    strcpy(empty_rec->description, "\0");
    strcpy(empty_rec->details, "\0");
    empty_rec->show = &show_record;
    empty_rec->add = &add_end;

    return empty_rec;
}

/*
 * Overloaded record constructor
 * parameter: id, unique identifier number
 * parameter: value, monetary value
 * parameter: datetime, data of datetime format
 * parameter: description, item description
 * parameter: category_id, item category
 * parameter: details, item details
 * return: record filled with data provided by parameters
 */
record* new_record_overloaded(size_t id, double value, DateTime datetime, char* description, size_t category_id, char* details)
{
    record* new_item = new_record();

    new_item->datetime = datetime;
    
    strncpy(new_item->description, description, MAX_DESCRIPTION);
    new_item->description[strlen(new_item->description)] = '\0';
    strncpy(new_item->details, details, MAX_DETAILS);
    new_item->details[strlen(new_item->details)] = '\0';

    new_item->category_id = category_id;
    new_item->value = value;
    new_item->id = id;

    return new_item;
}
