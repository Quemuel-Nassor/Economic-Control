/*
	This library contains a function to return date 
	of splitered and integer form
*/

//Dependencies
#include<time.h>

//DateTime struct
typedef struct datetime{
	char Date[11];
	char Month[11];
	char Year[5];
	char DateTimeNow[20];
	char Time[10];
}DateTime;

//Global variables
DateTime dateTime;

//Matrix of months of year
const char MonthsOfYear[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

//Function to get system date
void getDate(){
	
	//Struct for get system date
	struct tm * tm;
	
	//Read system datetime
	time_t t;
	time(&t);
	tm = localtime(&t);
		
	//Fills global struct DateTime
	strftime(dateTime.Date,11,"%d/%m/%Y", tm);
	strftime(dateTime.Month,11,"%B",tm);
	strftime(dateTime.Year,5,"%Y",tm);
	strftime(dateTime.DateTimeNow,20,"%Y-%m-%d %X",tm);
	strftime(dateTime.Time,10,"%X",tm);

}

