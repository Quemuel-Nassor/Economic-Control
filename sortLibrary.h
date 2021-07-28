/*
	This library contains functions to
	sort the recList by date, or by Id
	or by value
*/

//Dependencies
#include<string.h>
#include<unistd.h>

//Function to order recList by ascending date
/* record *orderByDate(record *recList){
	
	//Local variables
	record *aux, *percursor;
	
	//Check if recsList is empty
	if(recList == NULL|| strcmp(recList->date ,"\0") == 0){
		
		//Feedback if recsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to order!!!");
		sleep (2);
		
	}else{
	
		//Set start point of percursor
		percursor = navigate_to_start(recList);
			
		//percursor loop
		while(percursor != NULL){	
				
			//set aux variable value
			aux = percursor->next;
				
			//Aux loop
			 while(aux != NULL){
					
				//Check and sort the items in the list
				if(strcmp(percursor->date,aux->date)>0){
			 		
					percursor->next = aux->next;
					aux->next  != NULL ? aux->next->prev = percursor : 0;
					aux->prev = percursor->prev;
					percursor->prev != NULL ? percursor->prev->next = aux : 0;
					percursor->prev = aux;
					aux->next = percursor;
					percursor = aux;
				}
				aux = aux->next;
			}
			percursor = percursor->next;
		}
	}
	
	return navigate_to_start(recList);
} */

//Function to order recList by ascending id
record *orderById(record *recList){
	
	//Local variables
	record *aux, *percursor;
	
	//Check if recsList is empty
	if(recList == NULL/* || strcmp(recList->date ,"\0") == 0*/){
		
		//Feedback if recsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to order!!!");
		sleep (2);
		
	}else{
		
		//Set start point of percursor
		percursor = navigate_to_start(recList);
			
		//percursor loop
		while(percursor != NULL){	
				
			//set aux variable value
			aux = percursor->next;
				
			//Aux loop
			 while(aux != NULL){
					
				//Check and sort the items in the list
				if(percursor->id > aux->id){
			 		
					percursor->next = aux->next;
					aux->next  != NULL ? aux->next->prev = percursor : 0;
					aux->prev = percursor->prev;
					percursor->prev != NULL ? percursor->prev->next = aux : 0;
					percursor->prev = aux;
					aux->next = percursor;
					percursor = aux;
				}
				aux = aux->next;
			}
			percursor = percursor->next;
		}
	}
	
	return navigate_to_start(recList);
}

//Function to order recList by ascending value
record *orderByValue(record *recList){
	
	//Local variables
	record *aux, *percursor;
	
	//Check if recsList is empty
	if(recList == NULL/* || strcmp(recList->date ,"\0") == 0*/){
		
		//Feedback if recsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to order!!!");
		sleep (2);
		
	}else{
	
		//Set start point of percursor
		percursor = navigate_to_start(recList);
			
		//percursor loop
		while(percursor != NULL){	
				
			//set aux variable value
			aux = percursor->next;
				
			//Aux loop
			 while(aux != NULL){
					
				//Check and sort the items in the list
				if(percursor->value > aux->value){
			 		
					percursor->next = aux->next;
					aux->next  != NULL ? aux->next->prev = percursor : 0;
					aux->prev = percursor->prev;
					percursor->prev != NULL ? percursor->prev->next = aux : 0;
					percursor->prev = aux;
					aux->next = percursor;
					percursor = aux;
				}
				aux = aux->next;
			}
			percursor = percursor->next;
		}
	}
	
	return navigate_to_start(recList);
}
