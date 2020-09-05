/*
	This library contains functions to read data from files for memory,
	write data into files, and switch data base 
*/

//Dependencies
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

//Constants
#define L 1000
#define C 7

//Global variables and extern declarations
char matrixYears[L][C];
extern int sizeOfCategoryList;
extern char categoryList[LIN][COL];
extern char yearsPath[25];
extern char basePath[30];
extern FILE *dataBase;

//Function to load configurations
void loadConfig(char categoryList[LIN][COL]){
	
	//Local variables
	long start = 76;
	sizeOfCategoryList = 0;
	
	//Opening file in read mode
	FILE *file = fopen("config.txt","r");
	
	//Positioning file pointer
	fseek(file,start,SEEK_CUR);
	
	//Get categories, and increment sizeOfCategoryList
	while(fgets(categoryList[sizeOfCategoryList],COL,file) != NULL){
		sizeOfCategoryList++;
	}
	
	//Close the file
	fclose(file);
}

//Function to load data from txt file at data base to regList
reg *loadListFromTxt(reg *regList,FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30], strLine[500], value[100];
	int index, chrKeyCount;
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tCould not open the file %c%s%c !!!", 34,localPath,34);
		sleep(2);
		regList = NULL;
				
	}else{
		
		//Creating a new record and adding it to the regList
		reg *newRecord;
		initalizeString(value,100);
		initalizeString(strLine,500);
		
		//Reading file by lines
		setbuf(stdin,NULL);
		while(fgets(strLine,500,dataBase) != NULL){
			
			//Creating a new record to storage data
			newRecord = newReg();
			
			//Splitting line content
			chrKeyCount = 0;
			initalizeString(value,100);
			for(index = 0; index<strlen(strLine);index++){
				
				
				//Mapping key characters and separating content
				strLine[index] == '\t' && chrKeyCount == 1 ? initalizeString(value,100) : 0;
				strLine[index] != '\t' && chrKeyCount == 0 ? (value[strlen(value)] = strLine[index]) && (newRecord->id = atoi(value)) : 0;
				strLine[index] != '\t' && chrKeyCount == 1 ? (newRecord->date[strlen(newRecord->date)] = strLine[index]) : 0;
				strLine[index] != '\t' && chrKeyCount == 2 ? (value[strlen(value)] = strLine[index]) && (newRecord->value = atof(value)) : 0;
				strLine[index] != '\t' && chrKeyCount == 3 ? (newRecord->category[strlen(newRecord->category)] = strLine[index]) : 0;
				strLine[index] != '\t' && chrKeyCount == 4 ? (newRecord->description[strlen(newRecord->description)] = strLine[index]) : 0;
				strLine[index] != '\n' && chrKeyCount == 5 ? (newRecord->details[strlen(newRecord->details)] = strLine[index]) : 0;
				strLine[index] == '\t' ? chrKeyCount++ : 0;
			}
			
			//Insert file data into regList
			strcmp(regList->date,"") == 0 ? regList = newRecord : addEnd(regList,newRecord);
		};
		
		//Close the files
		fclose(dataBase);
	}
	
	//Returns list of content from file
	return regList;
}

//Function to load data from json file at data base to regList
reg *loadListFromJson(reg *regList,FILE *dataBase, char path[30]){
		
	//Local variables
	char localPath[30], strLine[500], value[100];
	int index, chrKeyCount;
	strcpy(localPath,path);
	strcat(localPath,".json");
		
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tCould not open the file %c%s%c !!!", 34,localPath,34);
		sleep(2);
		regList = NULL;
				
	}else{
		
//		//Creating a new record and adding it to the regList
//		reg *newRecord;
//		initalizeString(value,100);
//		initalizeString(strLine,500);
//		
//		//Reading file by lines
//		setbuf(stdin,NULL);
//		while(fgets(strLine,500,dataBase) != NULL){
//			
//			//Splitting line content
//			chrKeyCount = 0;
//			initalizeString(value,100);
//			for(index = 0; index<strlen(strLine);index++){
//				
//				if(strLine[index] == '{'){
//					
//					//Creating a new record to storage data
//					newRecord = newReg();
//					
//				}else if(strLine[index] == '}'){
//					
//					//Insert file data into regList
//					strcmp(regList->date,"") == 0 ? regList = newRecord : addEnd(regList,newRecord);
//					
//				}
//
//				if(newRecord != NULL){
//				
//				strLine[index] != ',' && strLine[index-2-strlen(value)] == ':' ? (strLine[index] != '"' ? value[strlen(value)] = strLine[index] : 0) : strLine[index] == ',' ? initalizeString(value,100) : 0;
//				strLine[index] != ',' && chrKeyCount == 0 ? (newRecord->id = atoi(value)) : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(newRecord->date)] == ':' && chrKeyCount == 1 ? strLine[index] != '"' ? (newRecord->date[strlen(newRecord->date)] = strLine[index]) : 0 : 0;
//				strLine[index] != ',' && chrKeyCount == 2 ? (newRecord->value = atof(value)) : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(newRecord->category)] == ':' && chrKeyCount == 3 ? strLine[index] != '"' ? (newRecord->category[strlen(newRecord->category)] = strLine[index]) : 0 : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(newRecord->description)] == ':' && chrKeyCount == 4 ? strLine[index] != '"' ? (newRecord->description[strlen(newRecord->description)] = strLine[index]) : 0 : 0;
//				strLine[index] != '}' && strLine[index-3-strlen(newRecord->details)] == ':' && chrKeyCount == 5 ? strLine[index] != '"' ? (newRecord->details[strlen(newRecord->details)] = strLine[index]) : 0 : 0;
//				strLine[index] != '{' && strLine[index] == ',' ? chrKeyCount++ : 0;
////				printf("\n\n id: %i\n date: %s\n category: %s\n value: %f\n description: %s\n details: %s",newRecord->id,newRecord->date,newRecord->category,newRecord->value,newRecord->description,newRecord->details);
////				setbuf(stdin,NULL);
////				getchar();
//				}
//				
//			}
////			printf("\n\nconteudo lido:\n id: %i\n date: %s\n category: %s\n value: %f\n description: %s\n details: %s",newRecord->id,newRecord->date,newRecord->category,newRecord->value,newRecord->description,newRecord->details);
////			setbuf(stdin,NULL);
////			getchar();
//			
//			//Insert file data into regList
////			strcmp(regList->date,"") == 0 ? regList = newRecord : addEnd(regList,newRecord);
//		};
//		
//		//Close the files
//		fclose(dataBase);
	}
	
	//Returns list of content from file
	return regList;
}

//Function to clean list
void cleanList(reg *regList){
	
	//Verifying if regList is null
	if(regList != NULL && regList->next != NULL){
			
		//Function call to remove records
		remEnd(regList);
		cleanList(regList);
		
	}
	regList = newReg();
}

//Function to write list to data base in format at txt
void saveListAsTxt(reg *regList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30];
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(regList != NULL){
		
		fprintf(dataBase,"%i\t",regList->id);
		fprintf(dataBase,"%s\t",regList->date);
		fprintf(dataBase,"%f\t",regList->value);
		fprintf(dataBase,"%s\t",regList->category);
		fprintf(dataBase,"%s\t",regList->description);
		fprintf(dataBase,"%s\n",regList->details);
	
		regList = regList->next,dataBase,path;
	}
	
	//Close the file
	fclose(dataBase);
}

//Function to write list to data base in format at json
void saveListAsJson(reg *regList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30];
	strcpy(localPath,path);
	strcat(localPath,".json");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(regList != NULL){
		
		regList->prev == NULL ? fprintf(dataBase,"%c",'[') : 0;
		
		fprintf(dataBase,"%c",'{');
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","id");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%i",regList->id);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","date");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->date);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","value");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%f",regList->value);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","category");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->category);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","description");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->description);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","details");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->details);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",'}');
		
		regList->next != NULL ? fprintf(dataBase,"%c",',') : 0;
	
		regList = regList->next;
	}
	fprintf(dataBase,"%c",']');
	
	//Close the file
	fclose(dataBase);
}

//Function to switch database
void switchDataBase(){
	
	//Local variables
	int i, countSeparators = 0, countYears = 0;
	char newPath[30], option, currentYear[7], currentMonth[11];
	
	//Loop to get year and month from current data base
	for(i=0;i<strlen(basePath);i++){
		
		//Get year
		if(basePath[i] != (char) DIRECTORY_SEPARATOR_CHAR[0] && countSeparators == 1){
			currentYear[i] = basePath[i];
		}
		
		//Get month
		if(basePath[i] != (char) DIRECTORY_SEPARATOR_CHAR[0] && countSeparators == 2){
			currentMonth[i] = basePath[i];
		}
		
		//Increase the count of directory separators
		basePath[i] == (char) DIRECTORY_SEPARATOR_CHAR[0] ? countSeparators++ : 0;
		
	}
	
	//Opens the year record in read mode
	FILE *yearList = fopen(yearsPath,"r");
	
	//Loop for fill matrix of years
	while(fscanf(yearList,"%s",matrixYears[countYears]) != EOF || (countYears == 1000)){
		countYears++;
	}
	
	//Close the file
	fclose(yearList);
	
	ClrScr();
	HEADER();
	printf("Active Database: %c%s%c\n\n",34,basePath,34);
	printf("Select a year\n\n");

	//loop to display and select years
	for(i=0;i<countYears;i++){

		i <= 8 ? printf(" ") : 0;
		printf("   %i - %s\n",i+1,matrixYears[i]);
	}

	//Get selected option
	setbuf(stdin,NULL);
	option = getchar()-48;

	//Checking if is currente or other
	if(strcmp(currentYear,matrixYears[option-1]) != 0){
		strcpy(currentYear, option-1 > countYears || option-1 < 0 ? currentYear : matrixYears[option-1]);
	}

	//Reset option
	option = '\0';	
	
	ClrScr();
	HEADER();
	printf("Active Database: %c%s%c\n\n",34,basePath,34);
	printf("Select a month\n\n");

	//loop to display and select months
	for(i=0;i<12;i++){
		
		i <= 8 ? printf(" ") : 0;
		printf("   %i - %s\n",i+1,MonthsOfYear[i]);
	}

	//Get selected option
	setbuf(stdin,NULL);
	option = getchar()-48;
		
	//Checking if is currente or other
	if(strcmp(currentMonth,MonthsOfYear[option-1]) != 0){
		strcpy(currentMonth, option-1 > 12 || option-1 < 0 ? currentMonth : MonthsOfYear[option-1]);
	}
	
	//Creating path to data base
	strcpy(basePath,"Database");
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	strcat(basePath,currentYear);
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	strcat(basePath,currentMonth);
	
	//Switch dataBase
	dataBase = fopen(basePath,"r");
	fclose(dataBase);
	
}
