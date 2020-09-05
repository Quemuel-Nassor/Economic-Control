/*
	This library contains a function to return date 
	of splitered and integer form
*/

//Dependencies
#include<time.h>

//Global strings to get date value
char Date[11];
char Month[11];
char Year[5];
char DateTimeNow[20];

//Function to get system date
void getDate(){
	
	//Struct for get system date
	struct tm * tm;
	time_t t;
	time(&t);
	tm = localtime(&t);
	
	//Fills global variables
	strftime(Date,11,"%d/%m/%Y", tm);
	strftime(Month,11,"%B",tm);
	strftime(Year,5,"%Y",tm);
	strftime(DateTimeNow,20,"%Y-%m-%d %X",tm);
	
}

