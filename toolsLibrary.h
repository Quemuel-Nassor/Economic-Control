/*	
	This library contains functions for obtaining date
	display records in recList, edit and search records
*/

//Dependencies
#include<ctype.h>
#include<unistd.h>
#include<stdio.h>

//Function to display records in the recList
void showRecords(record *ficha){
	
	//Local variables
	record *temp = ficha;
	int totalRecords = 0;
	double sumValue = 0;
	
	//Check if recsList is empty
	if(temp == NULL/* || strcmp(temp->date ,"\0") == 0*/){
		
		//Feedback if recsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to display!!!");
		sleep (2);
		
	}else{	
		
		//Loop to display records
		printf("----------------------------------------------------------------------------------------------------\n");
		while(temp != NULL){
			
			temp->show(temp);
			
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
void editRecord(record *recList){
	
	//Local variables
	record *temp = recList;
	int idKeyWord = 0;	
	
	//Receive idKeyWord to search
	ClrScr();
	HEADER();
	showRecords(recList);
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
