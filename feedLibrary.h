/*
	This library contains a function to fill data 
	in the new record
*/

//Dependencies
#include<string.h>
#include<stdio.h>
#include<ctype.h>

//Global variables
extern char categoryList[LIN][COL];
extern int sizeOfCategoryList;
extern DateTime dateTime;

//Function to get date value
void getNewDate(char input[20]){
	
	//Local variables
	int index;
	char newDate[20];
	strcpy(newDate,"\0");
	
	//Read new date and concatenate the add-on
	ClrScr();
	HEADER();
	printf("Enter a new date in YYYY-MM-DD format or press enter to default value: ");
	setbuf(stdin,NULL);
	fgets(newDate,11,stdin);
	
	if(strcmp(newDate,"\n") != 0){
			
		//Checking if input is valid
		for(index = 0; index < 11; index++){
			
			if((!isdigit(newDate[index]) && (index != 4 || index != 7)) || newDate[4] != '-' || newDate[7] != '-'){
				ClrScr();
				printf("Invalid entry, please try again!");
				sleep(2);
				getNewDate(input);
				break;
			}		
		}
	
		//Validating selection
		if(strcmp(newDate,"\0") != 0){
			
			//Insert the new value of date and concatenate the add-on
			newDate[strlen(newDate)-1] = ' ';
			// getDate();
			// strcat(newDate,dateTime.Time);
			strcpy(input,newDate);
		}
	}
}

//Function to get category
void getCategory(char input[COL]){
	
	//Menu to select category from record
	HEADER();
	printf("Select a category for record: \n\n");
	int count = 0, Index = 0;
	char selectedOption[4];
	
	//Display all categories in categoryList
	for(count = 0; count < sizeOfCategoryList-1; count++){
		count <= 8 ? printf(" ") : 0;
		printf("   %i - %s",count+1, categoryList[count]);
	}
	
	//Returns the selected category if the Index is in the range Index <= count or Index >= 0 if not return NULL
	setbuf(stdin,NULL);
	fgets(selectedOption,3,stdin);
	selectedOption[3] = '\0';
	Index = atoi(selectedOption);
	
	//Checking if is new or existing
	if(strcmp(input,"\0") == 0 || strcmp(input,categoryList[Index-1]) == 0){
		strcpy(input, (Index-1 > count || Index-1 < 0 ? "" : categoryList[Index-1]));
	}
}

//Function to generate ID
int getId(void){
	
	//Local variables
	long start = 73;
	char idFile[30];
	int Id = 0;
	
	//Opening file in read mode
	FILE *config = fopen("ID_increment.txt","r");

	//Positioning file pointer
	fseek(config,start,SEEK_CUR);
	
	//Get ID from file
	while(fgets(idFile,30,config)!=NULL);
	
	//Incrementing ID
	Id = atoi(idFile);
	Id++;
	
	//Close the file
	fclose(config);
	
	//Open File in write mode to write incremented ID
	config = fopen("ID_increment.txt","w");

	//Writing new file content
	fprintf(config,"%s","#This is a configuration file, don't delete or modify\n\n#ID incrementer:\n");
	fprintf(config,"%i",Id);
	
	//Close the file
	fclose(config);
	
	return Id;
}

//Function to fill the data of new record
void dataFeed(record *recsList){
	
	//Set id of recister
	recsList->id = recsList->id == 0 ? getId() : recsList->id;
	
	ClrScr();
	HEADER();
	printf("Id: %lu\n",recsList->id);
	
//Receives date data
//===================================================================
	
	//Get date input and checking if is new or existing
	// if(strcmp(recsList->date,"\0") == 0){
		
	// 	//Set the date of the new record to DateTimeNow
	// 	getDate();
	// 	strcpy(recsList->date,dateTime.DateTimeNow);
		
	// }else{
		
	// 	//Get new date to record
	// 	getNewDate(recsList->date);
		
	// }
	
	// printf("Date: %s",recsList->date);
	
//Receives description data
//===================================================================

	//Local variables
	char description[100];
	strcpy(description,recsList->description);
	
	//Get description input
	printf("\nDescription: ");
	setbuf(stdin,NULL);
	fgets(recsList->description,100,stdin);
	recsList->description[strlen(recsList->description)-1] = '\0';
	
	//Checking if is new or existing
	(strcmp(recsList->description,"\0") == 0 && strcmp(description,"\0") != 0) ? strcpy(recsList->description,description) : 0;
			
//Receives category data
//===================================================================
	
	//Get selected category to the recList
	ClrScr();
	// getCategory(recsList->category);
	// recsList->category[strlen(recsList->category)-1] = '\0';
	
	//Clean screen and display data
	ClrScr();
	HEADER();
	printf("Date: %s",recsList->datetime.format_string(recsList->datetime,DATETIME));
	printf("\nDescription: %s",recsList->description);
	// printf("\nCategory: %s",recsList->category);
					
//Receives value data
//===================================================================		
	
	//Local variables
	double Value = recsList->value;
	char value[100];
	
	//Get value input
	strcpy(value,"\0");
	printf("\nValue: ");
	setbuf(stdin,NULL);
	fgets(value,100,stdin);
	value[strlen(value)-1] = '\0';	
	
	//Set the value of the new record to NULL if it is empty
	Value != 0.00 && strcmp(value,"\0") == 0 ? 0 : Value == 0.00 && strcmp(value,"\0") != 0 ? (recsList->value = atof(value)) : Value != 0.00 && strcmp(value,"\0") != 0 ? (recsList->value = atof(value)) : 0;

	//Clean screen and display data
	ClrScr();
	HEADER();
	printf("Date: %s",recsList->datetime.format_string(recsList->datetime,DATETIME));
	printf("\nDescription: %s",recsList->description);
	// printf("\nCategory: %s",recsList->category);
	printf("\nValue: %.2lf",recsList->value);

//Receives details data
//===================================================================
	
	//Local variables
	char details[100];
	strcpy(details,recsList->details);
	
	//Get details input
	printf("\nDetails: ");
	setbuf(stdin,NULL);
	fgets(recsList->details,100,stdin);
	recsList->details[strlen(recsList->details)-1] = '\0';
	
	//Checking if is new or existing
	(strcmp(recsList->details,"\0") == 0 && strcmp(details,"\0") != 0) ? strcpy(recsList->details,details) : 0;
	
}	
