/*
 * This library contains a definition of the data type of the "DateTime" and methods to format and
 * get data from him
 *
 * Author: Quemuel Alves Nassor
 * Date: 02/05/21
 */

#ifndef DATETIME_H
#define DATETIME_H

#include <time.h>

/* Date time structure  */
typedef struct datetime
{
    struct tm* date;
    time_t time_secs;
    struct datetime (*now)(void);
    char* (*format_string)(struct datetime value);
    void (*set_month)(struct datetime* datetime, int month);
    void (*set_week_day)(struct datetime* datetime, int week_day);
    void (*set_year)(struct datetime* datetime, int year);
} DateTime;

/* Constants of months of year */
enum months_of_year
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER,
};

/* Max sizes constants */
enum dims
{
    MAX_DATETIME = 20,
    MAX_DATE = 11,
    MAX_TIME = 10,
    MAX_YEAR = 5,
    MAX_MONTH = 10,
    MAX_DAY = 3
};

DateTime now(void);
char* year(DateTime datetime);
int year_number(DateTime datetime);
char* month(DateTime datetime);
int month_number(DateTime datetime);
int day(DateTime datetime);
char* time_only(DateTime datetime);
char* datetime_string(DateTime datetime);
void set_month(DateTime* datetime, int month);
void set_week_day(DateTime* datetime, int week_day);
void set_year(DateTime* datetime, int year);
DateTime new_datetime(void);
DateTime new_datetime_overloaded(int seconds, int minutes, int hours, int month_day, int month, int year, int week_day, int year_day, int is_dst, time_t time_seconds);

#endif