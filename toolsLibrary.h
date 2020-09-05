/*	
	This library contains functions for obtaining date
	display records in regList, edit and search records
*/

//Dependencies
#include<ctype.h>
#include<unistd.h>
#include<stdio.h>

//Function to display records in the regList
void showRecords(reg *ficha){
	
	//Local variables
	reg *temp = ficha;
	int totalRecords = 0;
	double sumValue = 0;
	
	//Check if regsList is empty
	if(temp == NULL || strcmp(temp->date ,"\0") == 0){
		
		//Feedback if regsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to display!!!");
		sleep (2);
		
	}else{	
		
		//Loop to display records
		printf("----------------------------------------------------------------------------------------------------\n");
		while(temp != NULL){
			
			//Displays the record data
			printf("          Id: %i\n",temp->id);
			printf("          Date: %s\n",temp->date);
			printf("          Category: %s\n",temp->category);
			printf("          Description: %s\n",temp->description);
			printf("          Value: %.2f\n",temp->value);
			printf("          Details: %s\n",temp->details);
			printf("----------------------------------------------------------------------------------------------------\n");
			
			//Increment the sum value with the value of each record and the total number of records
			sumValue += temp->value;
			totalRecords++;			
			temp = temp->next;
		}
		
		//Displays the sum value
		printf("\n   =======================      ===========================\n    Total records: %i             Total sum: %.2f   \n   =======================      ===========================\n",totalRecords,sumValue);
	}
}

//Function to edit an record
void editRecord(reg *regList){
	
	//Local variables
	reg *temp = regList;
	int idKeyWord = 0;	
	
	//Receive idKeyWord to search
	ClrScr();
	HEADER();
	showRecords(regList);
	printf("\n\n   Enter the ID of the record to be edited: \n");
	
	//Input ID
	setbuf(stdin,NULL);
	idKeyWord = getchar()-48;	

	//Search loop 
	while(temp!= NULL){
		
		//Checking if is the searched record
		if((idKeyWord == temp->id)){
			
			//Editing record
			dataFeed(temp);
			break;
		}
		
		temp = temp->next;
		
		//Feedback default
		if(temp == NULL){
			ClrScr();
			HEADER();
			printf("\n\n\n\t\t\t\tWe didn't find anything, check the search ID and try again!");
			sleep (3);
		}
	}
}
