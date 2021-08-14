/*
 * This library contains a definition of the data type of the "DateTime" and methods to format and
 * get data from him
 *
 * Author: Quemuel Alves Nassor
 * Date: 02/05/21
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if defined(_WIN32) || defined(WIN32)
#include "..\include\date_time.h"
#elif defined(__unix__)
#include "../include/date_time.h"
#endif

const char* DATETIME_HANDLERS[] = {
    "%a %e %b %Y %T",  /* DEFAULT default format */
    "%c",              /* SHORT_DATETIME short datetime format */
    "%Y-%m-%d %T",     /* DATETIME full datetime format */
    "%Y-%m-%dT%T.000", /* DATABASE_UTC full datetime format for database (ISO 8601) */
    "%S",              /* SECOND seconds (00-61) */
    "%M",              /* MINUTE minutes (00-59) */
    "%I",              /* HOUR_12 hour in 24h format (00-23) */
    "%H",              /* HOUR_24 hour in 12h format (01-12) */
    "%r",              /* TIME_12 12-hour clock time format */
    "%R",              /* TIME_24 24-hour HH:MM time format */
    "%X",              /* FULL_TIME full time (HH:MM:SS)  */
    "%T",              /* FULL_TIME_ISO full time (HH:MM:SS) (ISO 8601) */
    "%a",              /* SHORT_WEEK_DAY_NAME abbreviated weekday name */
    "%A",              /* WEEK_DAY_NAME full weekday name */
    "%u",              /* WEEK_DAY_START_ONE weekday as number with Monday as 1 (1-7) (ISO 8601) */
    "%w",              /* WEEK_DAY_START_ZERO weekday as a decimal number with Sunday as 0 (0-6) */
    "%d",              /* MONTH_DAY_LEFT_ZERO day of the month, zero-padded (01-31) */
    "%e",              /* MONTH_DAY day of the month, space-padded ( 1-31) */
    "%j",              /* YEAR_DAY day of the year (001-366) */
    "%g",              /* SHORT_WEEK_BASED_YEAR week-based year, last two digits (00-99) */
    "%G",              /* WEEK_BASED_YEAR week-based year (2001) */
    "%U",              /* WEEK_START_SUNDAY_ZERO week number with the first Sunday as the first day of week one (00-53) */
    "%W",              /* WEEK_START_MONDAY_ZERO week number with the first Monday as the first day of week one (00-53) */
    "%V",              /* WEEK_START_ONE week number (01-53) (ISO 8601) */
    "%b",              /* SHORT_MONTH_NAME abbreviated month name */
    "%B",              /* FULL_MONTH_NAME full month name */
    "%m",              /* MONTH month as a decimal number (01-12) */
    "%C",              /* SHORT_YEAR_ROUNDED year divided by 100 and truncated to integer (00-99) */
    "%y",              /* SHORT_YEAR year, last two digits (00-99) */
    "%Y",              /* YEAR year 2001 */
    "%D",              /* SHORT_SHORT_DATE short MM/DD/YY date */
    "%F",              /* SHORT_DATE short YYYY-MM-DD date */
    "%z",              /* OFFSET_TIMEZONE offset from UTC in timezone (1 minute=1, 1 hour=100), if timezone cannot be determined, no characters (ISO 8601) */
    "%Z",              /* OFFSET_TIMEZONE_NAME timezone name or abbreviation *If timezone cannot be determined, no characters */
    "%p",              /* AM_PM AM or PM designation */
};

/*
 * Function to get current datetime
 * return: current datetime
 */
DateTime now(void)
{
    DateTime datetime;

    time(&datetime.time_seconds);
    datetime.date = localtime(&datetime.time_seconds);
    
    datetime.now = &now;
    datetime.format_string = &datetime_format;
    datetime.set_month = &set_month;
    datetime.set_week_day = &set_week_day;
    datetime.set_year = &set_year;

    return datetime;
}

/*
 * Function to convert string datetime to corresponding integer value
 * parameter: string_datetime, datetime string to convert
 * return: value converted to corresponding integer
 */
int get_value(char* string_datetime)
{
    return atoi(string_datetime);
}

/*
 * Function to get datetime string from datetime
 * parameter: datetime, data of datetime format
 * parameter: format, format to get result
 * return: datetime part as string
 */
char* datetime_format(DateTime datetime, int format)
{
    char* formated_datetime = (char*)malloc(DATETIME_MAX_LENGTH * sizeof(char));

    strftime(formated_datetime, DATETIME_MAX_LENGTH, DATETIME_HANDLERS[format], datetime.date);
    formated_datetime[strlen(formated_datetime)] = '\0';

    return formated_datetime;
}

/*
 * Function to set datetime month
 * parameter: datetime, data of datetime format
 * parameter: month, month number range 1 to 12
 */
void set_month(DateTime* datetime, int month)
{
    datetime->date->tm_mon = month - 1;
}

/*
 * Function to set datetime week day
 * parameter: datetime, data of datetime format
 * parameter: week_day, day of the week, range 1 to 7
 */
void set_week_day(DateTime* datetime, int week_day)
{
    datetime->date->tm_wday = week_day - 1;
}


/*
 * Function to set datetime year
 * parameter: datetime, data of datetime format
 * parameter: year, the number of years since 1900
 */
void set_year(DateTime* datetime, int year)
{
    datetime->date->tm_year = year - 1900;
}

/*
 * Function do initialize datetime from string
 * parameter: string_datetime, datetime in utc string format for database
 * return: datetime structure initialized
 */
DateTime datetime_from(char *string_datetime)
{
    int sz;
	char **datetime = string_split("T",string_datetime,&sz);
    char **date = string_split("-",datetime[0],&sz);
    char **time = string_split(":",datetime[1],&sz);
    char **secs = string_split(".",time[2],&sz);

    char *ano = date[0];
    char *mes = date[1];
    char *dia = date[2];
    char *hora = time[0];
    char *min = time[1];
    char *sec = secs[0];

	int ano_n = get_value(date[0]);
	int mes_n = get_value(date[1]);
	int dia_n = get_value(date[2]);
	int hora_n = get_value(time[0]);
	int min_n = get_value(time[1]);
	int sec_n = get_value(sec);

	DateTime result = new_datetime_overloaded(sec_n,min_n,hora_n,dia_n,mes_n,ano_n,0,0,0);
    return result;
}

/*
 * Default datetime constructor
 * return: minimally initialized datetime
 */
DateTime new_datetime(void)
{
    DateTime datetime;
    
    datetime = now();

    datetime.now = &now;
    datetime.format_string = &datetime_format;
    datetime.set_month = &set_month;
    datetime.set_week_day = &set_week_day;
    datetime.set_year = &set_year;

    return datetime;
}

/*
 * Overloaded datetime constructor
 * parameter: seconds, seconds,  range 0 to 59          
 * parameter: minutes, minutes, range 0 to 59           
 * parameter: hours, hours, range 0 to 23             
 * parameter: month_day, day of the month, range 1 to 31  
 * parameter: month, month, range 1 to 12             
 * parameter: year, The number of years since 1900   
 * parameter: week_day, day of the week, range 1 to 7    
 * parameter: year_day, day in the year, range 0 to 365  
 * parameter: is_dst, daylight saving time   
 * return: datetime filled with data provided by parameters
 */
DateTime new_datetime_overloaded(int seconds, int minutes, int hours, int month_day, int month, int year, int week_day, int year_day, int is_dst)
{
    DateTime datetime;

    datetime.date = (struct tm*)malloc(sizeof(struct tm));
    datetime.now = &now;
    datetime.format_string = &datetime_format;
    datetime.set_month = &set_month;
    datetime.set_week_day = &set_week_day;
    datetime.set_year = &set_year;

    datetime.date->tm_sec = seconds;               /* seconds,  range 0 to 59          */
    datetime.date->tm_min = minutes;               /* minutes, range 0 to 59           */
    datetime.date->tm_hour = hours;                /* hours, range 0 to 23             */
    datetime.date->tm_mday = month_day;            /* day of the month, range 1 to 31  */
    set_month(&datetime, month);                   /* month, range 1 to 12             */
    set_year(&datetime, year);                     /* The number of years since 1900   */
    set_week_day(&datetime, week_day);             /* day of the week, range 1 to 7    */
    datetime.date->tm_yday = year_day;             /* day in the year, range 0 to 365  */
    datetime.date->tm_isdst = is_dst;              /* daylight saving time             */
    datetime.time_seconds = mktime(datetime.date); /* time in seconds                  */

    return datetime;
}