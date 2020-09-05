/*
	This mainFile contains library additions and the basic 
	program execution and verification environment
*/

//Dependencies
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>

//Constants
#define LIN 50
#define COL 50

//Global variables 
char basePath[30] = "Database";
char yearsPath[25];
char categoryList[LIN][COL];
int sizeOfCategoryList;
FILE *dataBase;
FILE *yearList;

//Funtion to create directories
void ___mkdir (char *path);

//Defines '\' or '/' and mkdir on unix/windows environtments
#ifdef __unix__         
    
	const char *DIRECTORY_SEPARATOR_CHAR = "/";
	
	void ___mkdir (char *path){
		mkdir(path,0700);
	}

#elif defined(_WIN32) || defined(WIN32) 

	const char *DIRECTORY_SEPARATOR_CHAR = "\\";
	
	void ___mkdir (char *path){
   		mkdir(path);
	}

#endif

//Custom libraries 
#include"register.h"
#include"date.h"
#include"menu.h"

//Extern declarations
extern DateTime dateTime;

//Check data base
void checkDatabase(){
	
	//Local variables
	// char yearsPath[25];
	char dataBaseFileCheck[30]; 
	char itemResult[7]; 
	char filePathTxt[30]; 
	char filePathJson[30]; 
	
	//Creating path to list years
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	strcpy(yearsPath,basePath);
	strcat(yearsPath,"list_years.txt");
	
	//Call datetime function
	getDate();
	
	//Creating path to data base
	strcat(basePath,dateTime.Year);
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	
	//Creating path to check if a data base exists
	strcpy(dataBaseFileCheck,basePath);
	strcat(dataBaseFileCheck,"file_check.txt");
	
	//Checking if an old data base exists
	if((dataBase = fopen(dataBaseFileCheck,"rb")) == NULL){
        
		//Creating directory to data base
		___mkdir("Database");
		___mkdir(basePath);
		
		//Validating new data base
		dataBase = fopen(dataBaseFileCheck,"wb");
		fprintf(dataBase,"%s","file_check is an internal file, if it is modified or deleted the program may not work correctly");
		
		//Close the file
		fclose(dataBase);
		
		//Concatenate current month
		strcat(basePath,dateTime.Month);
		strcpy(filePathTxt,basePath);
		strcpy(filePathJson,basePath);
		
		//Concatenate file extensions
		strcat(filePathTxt,".txt");
		strcat(filePathJson,".json");
		
		//Write new files
		dataBase = fopen(filePathJson,"w");
		dataBase = fopen(filePathTxt,"w");
		
		//Opening list of years in append mode
		yearList = fopen(yearsPath,"a");
		
		//Write the current year in the file
			fprintf(yearList,"%s",dateTime.Year);
			fprintf(yearList,"%c",'\n');
		
		//Close the file
		fclose(yearList);
		fclose(dataBase);
		
	}else{
		
		//Concatenate current month
		strcat(basePath,dateTime.Month);
	}
	
	//Opening list of years in append mode
	yearList = fopen(yearsPath,"a");		
	
	//Search current year in file
	while(fscanf(yearList,"%s",itemResult) != EOF){

		//Add current year in file if don't exist
		if(atoi(itemResult) == EOF && strcmp(itemResult,dateTime.Year) != 0){
			
			//Write the current year in the file
			fprintf(yearList,"%s",dateTime.Year);
			fprintf(yearList,"%c",'\n');
			
		}else if (atoi(itemResult) != EOF && strcmp(itemResult,dateTime.Year) == 0){
			
			break;
		}
		
	}
	
	//Close the files
	fclose(yearList);
}

//Main function
int main(){
	
	//Call checks data base function
	checkDatabase();
	
	//Load category list
	loadConfig(categoryList);
	
	//Call menu program function
	Menu(newReg(),basePath,dataBase);

	return(0);
}

