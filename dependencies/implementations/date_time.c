/*
 * This library contains a definition of the data type of the "DateTime" and methods to format and
 * get data from him
 *
 * Author: Quemuel Alves Nassor
 * Date: 02/05/21
 */

#include <stdlib.h>

#if defined(_WIN32) || defined(WIN32)
#include "..\include\date_time.h"
#elif defined(__unix__)
#include "../include/date_time.h"
#endif

/*
 * Function to get current datetime
 * return: current datetime
 */
DateTime now(void)
{
    DateTime datetime;

    time(&datetime.time_secs);
    datetime.date = localtime(&datetime.time_secs);
    
    datetime.now = &now;
    datetime.format_string = &datetime_string;
    datetime.set_month = &set_month;
    datetime.set_week_day = &set_week_day;
    datetime.set_year = &set_year;

    return datetime;
}

/*
 * Function to get year from datetime
 * parameter: datetime, data of datetime format
 * return: year from datetime as string
 */
char* year(DateTime datetime)
{
    char* year = (char*)malloc(MAX_YEAR * sizeof(char));

    strftime(year, MAX_YEAR, "%Y", datetime.date);
    year[MAX_YEAR - 1] = '\0';

    return year;
}

/*
 * Function to get year number from datetime
 * parameter: datetime, data of datetime format
 * return: year from datetime as number
 */
int year_number(DateTime datetime)
{
    char year[MAX_YEAR];

    strftime(year, MAX_YEAR, "%Y", datetime.date);

    return atoi(year);
}

/*
 * Function to get month name from datetime
 * parameter: datetime, data of datetime format
 * return: month name from datetime
 */
char* month(DateTime datetime)
{
    char* month = (char*)malloc(MAX_MONTH * sizeof(char));

    strftime(month, MAX_MONTH, "%B", datetime.date);
    month[MAX_MONTH - 1] = '\0';

    return month;
}

/*
 * Function to get number of month from datetime
 * parameter: datetime, data of datetime format
 * return: number of month from datetime
 */
int month_number(DateTime datetime)
{
    char month[MAX_DAY];

    strftime(month, MAX_DAY, "%m", datetime.date);

    return atoi(month);
}

/*
 * Function to get day from datetime
 * parameter: datetime, data of datetime format
 * return: number of day from datetime
 */
int day(DateTime datetime)
{
    char day[MAX_DAY];

    strftime(day, MAX_DAY, "%d", datetime.date);

    return atoi(day);
}

/*
 * Function to get time from datetime
 * parameter: datetime, data of datetime format
 * return: time from datetime as string
 */
char* time_only(DateTime datetime)
{
    char* time = (char*)malloc(MAX_TIME * sizeof(char));

    strftime(time, MAX_TIME, "%X", datetime.date);
    time[MAX_TIME - 1] = '\0';

    return time;
}

/*
 * Function to get datetime string from datetime
 * parameter: datetime, data of datetime format
 * return: datetime as string
 */
char* datetime_string(DateTime datetime)
{
    char* string_datetime = (char*)malloc(MAX_DATETIME * sizeof(char));

    strftime(string_datetime, MAX_DATETIME, "%Y-%m-%d %X", datetime.date);
    string_datetime[MAX_DATETIME - 1] = '\0';

    return string_datetime;
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
 * Default datetime constructor
 * return: minimally initialized datetime
 */
DateTime new_datetime(void)
{
    DateTime datetime;
    
    datetime = now();

    datetime.now = &now;
    datetime.format_string = &datetime_string;
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
 * parameter: time_seconds, the number of seconds since 1900 
 * return: datetime filled with data provided by parameters
 */
DateTime new_datetime_overloaded(int seconds, int minutes, int hours, int month_day, int month, int year, int week_day, int year_day, int is_dst, time_t time_seconds)
{
    DateTime datetime;

    datetime.date = (struct tm*)malloc(sizeof(struct tm));
    datetime.now = &now;
    datetime.format_string = &datetime_string;
    datetime.set_month = &set_month;
    datetime.set_week_day = &set_week_day;
    datetime.set_year = &set_year;

    datetime.date->tm_sec = seconds;      /* seconds,  range 0 to 59          */
    datetime.date->tm_min = minutes;      /* minutes, range 0 to 59           */
    datetime.date->tm_hour = hours;       /* hours, range 0 to 23             */
    datetime.date->tm_mday = month_day;   /* day of the month, range 1 to 31  */
    set_month(&datetime, month);          /* month, range 1 to 12             */
    set_year(&datetime, year);            /* The number of years since 1900   */
    set_week_day(&datetime, week_day);    /* day of the week, range 1 to 7    */
    datetime.date->tm_yday = year_day;    /* day in the year, range 0 to 365  */
    datetime.date->tm_isdst = is_dst;     /* daylight saving time             */
    datetime.time_secs = time_seconds;    /* the number of seconds since 1900 */

    return datetime;
}