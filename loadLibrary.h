/*
	This library contains functions to read data from files for memory,
	write data into files, and switch data base 
*/

//Dependencies
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "dependencies/include/dir_mgmt.h"
#include "dependencies/include/date_time.h"
#include "dependencies/include/string_handler.h"
#include "dependencies/include/file.h"

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

//Function to load data from txt file at data base to recList
record *loadListFromTxt(record *recList,FILE *dataBase, char path[30]){
	
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
		recList = NULL;
				
	}else{
		
		//Creating a new record and adding it to the recList
		record *new_rec;
		strcpy(value,"\0");
		strcpy(strLine,"\0");
		
		//Reading file by lines
		setbuf(stdin,NULL);
		while(fgets(strLine,500,dataBase) != NULL){
			
			//Creating a new record to storage data
			new_rec = new_record();
			
			//Splitting line content
			chrKeyCount = 0;
			strcpy(value,"\0");
			for(index = 0; index<strlen(strLine);index++){
				
				
				//Mapping key characters and separating content
				if (strLine[index] == '\t' && chrKeyCount == 1) strcpy(value,"\0");
				if (strLine[index] != '\t' && chrKeyCount == 0) {(value[strlen(value)] = strLine[index]); (new_rec->id = atoi(value));}
				// strLine[index] != '\t' && chrKeyCount == 1 ? (new_rec->date[strlen(new_rec->date)] = strLine[index]) : 0;
				if(strLine[index] != '\t' && chrKeyCount == 2){ (value[strlen(value)] = strLine[index]); (new_rec->value = atof(value));}
				// if(strLine[index] != '\t' && chrKeyCount == 3){ (new_rec->category[strlen(new_rec->category)] = strLine[index]);}
				if(strLine[index] != '\t' && chrKeyCount == 4){ (new_rec->description[strlen(new_rec->description)] = strLine[index]);}
				if(strLine[index] != '\n' && chrKeyCount == 5){ (new_rec->details[strlen(new_rec->details)] = strLine[index]);}
				if(strLine[index] == '\t') chrKeyCount++;
			}
			
			//Insert file data into recList
			// strcmp(recList->date,"") == 0 ? recList = new_rec : addEnd(recList,new_rec);
		};
		
		//Close the files
		fclose(dataBase);
	}
	
	//Returns list of content from file
	return recList;
}

//Function to load data from json file at data base to recList
record *loadListFromJson(record *recList,FILE *dataBase, char path[30]){
		
	//Local variables
	char localPath[30];//, strLine[500], value[100];
	// int index, chrKeyCount;
	strcpy(localPath,path);
	strcat(localPath,".json");
		
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tCould not open the file %c%s%c !!!", 34,localPath,34);
		sleep(2);
		recList = NULL;
				
	}else{
		
//		//Creating a new record and adding it to the recList
//		record *new_rec;
//		strcpy(value,"\0");
//		strcpy(strLine,"\0");
//		
//		//Reading file by lines
//		setbuf(stdin,NULL);
//		while(fgets(strLine,500,dataBase) != NULL){
//			
//			//Splitting line content
//			chrKeyCount = 0;
//			strcpy(value,"\0");
//			for(index = 0; index<strlen(strLine);index++){
//				
//				if(strLine[index] == '{'){
//					
//					//Creating a new record to storage data
//					new_rec = new_record();
//					
//				}else if(strLine[index] == '}'){
//					
//					//Insert file data into recList
//					strcmp(recList->date,"") == 0 ? recList = new_rec : addEnd(recList,new_rec);
//					
//				}
//
//				if(new_rec != NULL){
//				
//				strLine[index] != ',' && strLine[index-2-strlen(value)] == ':' ? (strLine[index] != '"' ? value[strlen(value)] = strLine[index] : 0) : strLine[index] == ',' ? strcpy(value,"\0"0;
//				strLine[index] != ',' && chrKeyCount == 0 ? (new_rec->id = atoi(value)) : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(new_rec->date)] == ':' && chrKeyCount == 1 ? strLine[index] != '"' ? (new_rec->date[strlen(new_rec->date)] = strLine[index]) : 0 : 0;
//				strLine[index] != ',' && chrKeyCount == 2 ? (new_rec->value = atof(value)) : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(new_rec->category)] == ':' && chrKeyCount == 3 ? strLine[index] != '"' ? (new_rec->category[strlen(new_rec->category)] = strLine[index]) : 0 : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(new_rec->description)] == ':' && chrKeyCount == 4 ? strLine[index] != '"' ? (new_rec->description[strlen(new_rec->description)] = strLine[index]) : 0 : 0;
//				strLine[index] != '}' && strLine[index-3-strlen(new_rec->details)] == ':' && chrKeyCount == 5 ? strLine[index] != '"' ? (new_rec->details[strlen(new_rec->details)] = strLine[index]) : 0 : 0;
//				strLine[index] != '{' && strLine[index] == ',' ? chrKeyCount++ : 0;
////				printf("\n\n id: %i\n date: %s\n category: %s\n value: %f\n description: %s\n details: %s",new_rec->id,new_rec->date,new_rec->category,new_rec->value,new_rec->description,new_rec->details);
////				setbuf(stdin,NULL);
////				getchar();
//				}
//				
//			}
////			printf("\n\nconteudo lido:\n id: %i\n date: %s\n category: %s\n value: %f\n description: %s\n details: %s",new_rec->id,new_rec->date,new_rec->category,new_rec->value,new_rec->description,new_rec->details);
////			setbuf(stdin,NULL);
////			getchar();
//			
//			//Insert file data into recList
////			strcmp(recList->date,"") == 0 ? recList = new_rec : addEnd(recList,new_rec);
//		};
//		
//		//Close the files
//		fclose(dataBase);
	}
	
	//Returns list of content from file
	return recList;
}

//Function to write list to data base in format at txt
void saveListAsTxt(record *recList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30];
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(recList != NULL){
		
		fprintf(dataBase,"%lu\t",recList->id);
		fprintf(dataBase,"%s\t",recList->datetime.format_string(recList->datetime,DATABASE_UTC));
		fprintf(dataBase,"%Lf\t",recList->value);
		fprintf(dataBase,"%lu\t",recList->category_id);
		fprintf(dataBase,"%s\t",recList->description);
		fprintf(dataBase,"%s\n",recList->details);
	
		recList = recList->next;
	}
	
	//Close the file
	fclose(dataBase);
}

//Function to write list to data base in format at json
void saveListAsJson(record *recList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30];
	strcpy(localPath,path);
	strcat(localPath,".json");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(recList != NULL){
		
		recList->prev == NULL ? fprintf(dataBase,"%c",'[') : 0;
		
		fprintf(dataBase,"%c",'{');
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","id");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%lu",recList->id);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","date");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->datetime.format_string(recList->datetime,DATABASE_UTC));
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","value");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%Lf",recList->value);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","category");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%lu",recList->category_id);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","description");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->description);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","details");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->details);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",'}');
		
		recList->next != NULL ? fprintf(dataBase,"%c",',') : 0;
	
		recList = recList->next;
	}
	fprintf(dataBase,"%c",']');
	
	//Close the file
	fclose(dataBase);
}

//Function to switch database
void switchDataBase(void){
	
	//Local variables
	int i, countSeparators = 0, countYears = 0, option = 0;
	char /*newPath[30],*/ chrOption[6], currentYear[7], currentMonth[11];
	
	//Loop to get year and month from current data base
	for(i=0;i<strlen(basePath);i++){
		
		//Get year
		if(basePath[i] != DIR_SEPARATOR_CHR && countSeparators == 1){
			currentYear[i] = basePath[i];
		}
		
		//Get month
		if(basePath[i] != DIR_SEPARATOR_CHR && countSeparators == 2){
			currentMonth[i] = basePath[i];
		}
		
		//Increase the count of directory separators
		basePath[i] == DIR_SEPARATOR_CHR ? countSeparators++ : 0;
		
	}
	
	//Opens the year record in read mode
	FILE *yearList = fopen(yearsPath,"r");
	
	//Loop for fill matrix of years
	while(fscanf(yearList,"%s",matrixYears[countYears]) != EOF || (countYears == 999)){
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
	fgets(chrOption,5,stdin);
	chrOption[5] = '\0';
	option = atoi(chrOption);

	//Checking if is currente or other
	if(strcmp(currentYear,matrixYears[option-1]) != 0){
		strcpy(currentYear, option-1 > countYears || option-1 < 0 ? currentYear : matrixYears[option-1]);
	}

	//Reset option
	chrOption[0] = '\0';
	option = 0;
	
	ClrScr();
	HEADER();
	printf("Active Database: %c%s%c\n\n",34,basePath,34);
	printf("Select a month\n\n");

	DateTime display = new_datetime();
	display.set_month(&display,option-1);

	//loop to display and select months
	for(i=JANUARY;i<DECEMBER;i++){
		display.set_month(&display,i);
		i <= 8 ? printf(" ") : 0;
		printf("   %i - %s\n",i,display.format_string(display,MONTH));
	}

	//Get selected option
	setbuf(stdin,NULL);
	fgets(chrOption,3,stdin);
	chrOption[5] = '\0';
	option = atoi(chrOption);
	display.date->tm_mon = option-1;
		
	//Checking if is currente or other
	if(strcmp(currentMonth, display.format_string(display,MONTH)) != 0){
		strcpy(currentMonth, option-1 > 12 || option-1 < 0 ? currentMonth : display.format_string(display,MONTH));
	}
	
	//Creating path to data base
	join_path(basePath,"Database");
	join_path(basePath,currentYear);
	join_path(basePath,currentMonth);
	// strcpy(basePath,"Database");
	// strcat(basePath,(char*)DIR_SEPARATOR_CHR);
	// strcat(basePath,currentYear);
	// strcat(basePath,(char*)DIR_SEPARATOR_CHR);
	// strcat(basePath,currentMonth);
	
	//Switch dataBase
	dataBase = fopen(basePath,"r");
	fclose(dataBase);
	
}

//Function to check yearsPath directory
void checkYearsPath(void){
	
	char itemResult[7]; 
	DateTime dtm = now();
	
	//Opening list of years in append mode
	yearList = fopen(yearsPath,"a");		
	
	//Search current year in file
	while(fscanf(yearList,"%s",itemResult) != EOF){

		//Add current year in file if don't exist
		if(atoi(itemResult) == EOF && atoi(itemResult) == get_value(dtm.format_string(dtm,YEAR))){
			
			//Write the current year in the file
			fprintf(yearList,"%s",dtm.format_string(dtm,YEAR));
			fprintf(yearList,"%c",'\n');
			
		}else if (atoi(itemResult) != EOF && atoi(itemResult) == get_value(dtm.format_string(dtm,YEAR))){
			
			break;
		}
	}
	
	//Close the files
	fclose(yearList);
}

//Check data base
void checkDatabase(void){
	
	//Local variables
	char dataBaseFileCheck[30]; 
	char filePathTxt[30]; 
	char filePathJson[30]; 
	
	DateTime dtm = now();
	
	//Creating path to list years
	// strcat(basePath,(char*)DIR_SEPARATOR_CHR);
	basePath[strlen(basePath)] = DIR_SEPARATOR_CHR;
	strcpy(yearsPath,basePath);
	strcat(yearsPath,"list_years.txt");
	
	//Call datetime function
	// getDate();
	
	// char y_str[5];
	// snprintf(y_str,5,"%d",year_number(dtm));

	//Creating path to data base
	strcat(basePath,dtm.format_string(dtm,YEAR));
	// strcat(basePath,(char*)DIR_SEPARATOR_CHR);
	basePath[strlen(basePath)] = DIR_SEPARATOR_CHR;
	
	//Creating path to check if a data base exists
	strcpy(dataBaseFileCheck,basePath);
	strcat(dataBaseFileCheck,"file_check.txt");
	
	//Checking if an old data base exists
	if((dataBase = fopen(dataBaseFileCheck,"rb")) == NULL){
        
		//Creating directory to data base
		mk_dir("Database");
		// ___mkdir(basePath);

		mk_dir(basePath);
		
		//Validating new data base
		dataBase = fopen(dataBaseFileCheck,"wb");
		fprintf(dataBase,"%s","file_check is an internal file, if it is modified or deleted the program may not work correctly");
		
		//Close the file
		fclose(dataBase);
		
		//Concatenate current month
		strcat(basePath,dtm.format_string(dtm,MONTH_NAME));
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
			fprintf(yearList,"%s",dtm.format_string(dtm,YEAR));
			fprintf(yearList,"%c",'\n');
		
		//Close the file
		fclose(yearList);
		fclose(dataBase);
		
	}else{
		
		//Concatenate current month
		strcat(basePath,dtm.format_string(dtm,MONTH));
	}
	
	checkYearsPath();
}


typedef struct year
{
    struct year* prev;
    struct year* next;
	size_t id;
	int year;
} YearRecord;

void checkDatabase2(){
	DateTime dtm = new_datetime();
	char db_path[PATH_MAX]="\0", db_index_path[PATH_MAX]="\0", db_years_path[PATH_MAX]="\0";
	char *content = "\0";

	YearRecord *yearsList = (YearRecord*)malloc(sizeof(YearRecord));
	yearsList->id = 1;
	yearsList->year = get_value(dtm.format_string(dtm,YEAR));
	
	join_path(db_path, "Database", NULL);
	join_path(db_index_path, "Database", "db_index.json", NULL);
	join_path(db_years_path, "Database", dtm.format_string(dtm,YEAR), NULL);

	/* Checks and manages the database directory */	
	if(check_if_dir_exist(db_path) != EXIT_SUCCESS)
	{
		mk_dir_tree(db_path);
		content = string_join(INDEFINITE_LENGTH,EMPTY_SEPARATOR,"[{\"id\": ",yearsList->id,",\"year\": ",yearsList->year,"}]",NULL);
	}
	else
	{
		int size = get_file_size(db_index_path) + 16;
		content = (char*)malloc(sizeof(char)*size);
		strncpy(content, read_file(READ, db_index_path), size-17);
		strcat(content,string_join(INDEFINITE_LENGTH,EMPTY_SEPARATOR,",{\"id\": ",yearsList->id,",\"year\": ",yearsList->year,"}]",NULL));
	}

	write_file(content, WRITE, db_index_path);
	free(content);
	
	/* Check and manage dabatase index files */	
	if(check_if_dir_exist(db_years_path) != EXIT_SUCCESS)
	{
		mk_dir_tree(db_years_path);
		join_path(db_years_path,strcat(dtm.format_string(dtm,MONTH_NAME),".json"),NULL);
		content = (char*)malloc(sizeof(char));
		strcpy(content,"\0");
	}
	else
	{
		join_path(db_years_path,strcat(dtm.format_string(dtm,MONTH_NAME),".json"),NULL);
		int size = get_file_size(db_years_path) + 16;
		strncpy(content, read_file(READ, db_years_path), size-17);
		strcat(content,string_join(INDEFINITE_LENGTH,EMPTY_SEPARATOR,",{\"year\": ",dtm.format_string(dtm,YEAR),"}]",NULL));
	}

	write_file(content, WRITE, db_years_path);
	free(content);

	

}

