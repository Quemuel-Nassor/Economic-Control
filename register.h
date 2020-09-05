/*
	This library contains a definition of the
	data type of the "reg" and methods to 
	manipulate dinamic lists of him
*/

//Dependencies
#include<stdio.h>
#include<stdlib.h>

//Dinamic data struct for lists
typedef struct regType{
	struct regType *prev; 
	struct regType *next;
	int id; 
	char description[100];
	char category[50];	
	char details[100]; 
	char date[20];		
	double value;		
}reg;

//Function to initalize strings
void initalizeString(char* String, int Size){
	int i;
	for(i=Size-1;i > -1; i--){										//Scroll the vector from the end to the beginning
		String[i] = '\0';											//Set \0 character in each position
	};
}

//Create an empty register
reg *newReg(){
    reg *emptyReg = (reg *)malloc(sizeof(reg));						//Allocates *reg size memory
    emptyReg->next = emptyReg->prev = NULL;							//Initalize poiters with NULL
    initalizeString(emptyReg->date,20);								//Initialize date with \0
    initalizeString(emptyReg->description,100);						//Initialize description with \0
    initalizeString(emptyReg->category,50);							//Initialize category with \0
    initalizeString(emptyReg->details,100);							//Initialize details with \0
    emptyReg->value = 0.00;											//Initialize value with 0.00
    emptyReg->id = 0;												//Initialize id with 0
    return emptyReg;
}

//Returns to the end of the list
reg *navEnd(reg *regsList){
	return (regsList->next != NULL ? navEnd(regsList->next) : regsList);
};

//Returns to the beginning of the list
reg *navStart(reg *regsList){
	return (regsList->prev != NULL ? navStart(regsList->prev) : regsList);
};

//Add a new item at the beginning of the list
reg *addStart(reg *regsList, reg *newItem){
	regsList = navStart(regsList);
	newItem->prev = regsList->prev;
	regsList->prev = newItem;
	newItem->next = regsList;
	return newItem;
};

//Add a new item at the middle of the list
reg *addMiddle(reg *regsList, reg *newItem){
	newItem->next = regsList->next;
	regsList->next != NULL ? regsList->next->prev = newItem : 0;
	newItem->prev = regsList;
	regsList->next = newItem;
	return navStart(regsList);
};

//Add a new item to the end of the list
void addEnd(reg *regsList, reg *newItem){
	regsList = navEnd(regsList);
	newItem->prev = regsList;
	newItem->next = regsList->next;
	regsList->next = newItem;
};

//Remove the first item at the beginning of the list
reg *remStart(reg *regsList){
	regsList = navStart(regsList);
	reg *temp = regsList->next;
	(temp != NULL) ? (temp->prev = regsList->prev) : 0;
	free(regsList);
	return temp;
};

//Remove an item in the middle of the list
reg *remMiddle(reg *regsList){
	reg *temp = navStart(regsList);
	if(regsList->prev != NULL && regsList->next != NULL){
		regsList->prev->next = regsList->next;
		regsList->next->prev = regsList->prev;
		free(regsList);
	}
	return temp;
};

//Remove the last item at the end of the list
void remEnd(reg *regsList){
	regsList = navEnd(regsList);
	(regsList->prev != NULL) ? (regsList->prev->next = regsList->next) : 0;
	free(regsList);
};
