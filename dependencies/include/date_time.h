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
#include "string_handler.h"

#define DATETIME_MAX_LENGTH 60
extern const char* DATETIME_HANDLERS[];

/* Date time structure  */
typedef struct datetime
{
    struct tm* date;
    time_t time_seconds;
    struct datetime (*now)(void);
    char* (*format_string)(struct datetime value, int format);
    void (*set_month)(struct datetime* datetime, int month);
    void (*set_week_day)(struct datetime* datetime, int week_day);
    void (*set_year)(struct datetime* datetime, int year);
} DateTime;

/* Constants of datetime formatters */
enum datetime_formats
{
    DEFAULT_DATETIME,        /* (%a %e %b %Y %T) default format */
    SHORT_DATETIME,          /* (%c) short datetime format */
    DATETIME,                /* (%Y-%m-%d %T) full datetime format */
    DATABASE_UTC,            /* (%Y-%m-%dT%T.000) full datetime format for database (ISO 8601) */
    SECOND,                  /* (%S) seconds (00-61) */
    MINUTE,                  /* (%M) minutes (00-59) */
    HOUR_12,                 /* (%I) hour in 24h format (00-23) */
    HOUR_24,                 /* (%H) hour in 12h format (01-12) */
    TIME_12,                 /* (%r) 12-hour clock time format */
    TIME_24,                 /* (%R) 24-hour HH:MM time format */
    FULL_TIME,               /* (%X) full time (HH:MM:SS)  */
    FULL_TIME_ISO,           /* (%T) full time (HH:MM:SS) (ISO 8601) */
    SHORT_WEEK_DAY_NAME,     /* (%a) abbreviated weekday name */
    WEEK_DAY_NAME,           /* (%A) full weekday name */
    WEEK_DAY_START_ONE,      /* (%u) weekday as number with Monday as 1 (1-7) (ISO 8601) */
    WEEK_DAY_START_ZERO,     /* (%w) weekday as a decimal number with Sunday as 0 (0-6) */
    MONTH_DAY_LEFT_ZERO,     /* (%d) day of the month, zero-padded (01-31) */
    MONTH_DAY,               /* (%e) day of the month, space-padded ( 1-31) */
    YEAR_DAY,                /* (%j) day of the year (001-366) */
    SHORT_WEEK_BASED_YEAR,   /* (%g) week-based year, last two digits (00-99) */
    WEEK_BASED_YEAR,         /* (%G) week-based year (2001) */
    WEEK_START_SUNDAY_ZERO,  /* (%U) week number with the first Sunday as the first day of week one (00-53) */
    WEEK_START_MONDAY_ZERO,  /* (%W) week number with the first Monday as the first day of week one (00-53) */
    WEEK_START_ONE,          /* (%V) week number (01-53) (ISO 8601) */
    SHORT_MONTH_NAME,        /* (%b) abbreviated month name */
    MONTH_NAME,              /* (%B) full month name */
    MONTH,                   /* (%m) month as a decimal number (01-12) */
    SHORT_YEAR_ROUNDED,      /* (%C) year divided by 100 and truncated to integer (00-99) */
    SHORT_YEAR,              /* (%y) year, last two digits (00-99) */
    YEAR,                    /* (%Y) year 2001 */
    SHORT_SHORT_DATE,        /* (%D) short MM/DD/YY date */
    SHORT_DATE,              /* (%F) short YYYY-MM-DD date */
    OFFSET_TIMEZONE,         /* (%z) offset from UTC in timezone (1 minute=1, 1 hour=100), if timezone cannot be determined, no characters (ISO 8601) */
    OFFSET_TIMEZONE_NAME,    /* (%Z) timezone name or abbreviation *If timezone cannot be determined, no characters */
    AM_PM                    /* (%p) AM or PM designation */
};

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

DateTime now(void);
int get_value(char *string_datetime);
char* datetime_format(DateTime datetime, int format);
void set_month(DateTime* datetime, int month);
void set_week_day(DateTime* datetime, int week_day);
void set_year(DateTime* datetime, int year);
// DateTime datetime_from(char *string_datetime);
DateTime new_datetime(void);
DateTime new_datetime_overloaded(int seconds, int minutes, int hours, int month_day, int month, int year, int week_day, int year_day, int is_dst);

#endif