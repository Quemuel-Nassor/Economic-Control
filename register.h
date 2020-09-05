/*
	This library contains a definition of the
	data type of the "reg" and methods to 
	manipulate dinamic lists of him
*/

//Dependencies
#include<stdio.h>
#include<stdlib.h>

//Dinamic data struct for lists
typedef struct dataType{
	struct dataType *ant; 
	struct dataType *prox; 
	char description[100];
	char category[14];	
	char details[100]; 
	char date[11];		
	double value;		
}reg;

//Function to initalize strings
void initalizeString(char* String, int Size){
	int i;
	for(i=Size-1;i > -1; i--){										//Scroll the vector from the end to the beginning
		String[i] = '\0';											//Set \0 character in each position
	};
}

//Create an empty reg
reg *newReg(){
    reg *emptyReg = (reg *)malloc(sizeof(reg));						//Allocates *reg size memory
    emptyReg->prox = emptyReg->ant = NULL;							//Initalize poiters with NULL
    initalizateString(emptyReg->date,11);							//Initialize date with \0
    initalizateString(emptyReg->description,100);					//Initialize description with \0
    initalizateString(emptyReg->category,14);						//Initialize category with \0
    initalizateString(emptyReg->details,100);						//Initialize details with \0
    emptyReg->value = 0.00;											//Initialize value with 0.00
    return emptyReg;
}

//Returns to the end of the list
reg *navEnd(reg *regsList){
	return (regsList->prox != NULL ? navEnd(regsList->prox) : regsList);
};

//Returns to the beginning of the list
reg *navStart(reg *regsList){
	return (regsList->ant != NULL ? navStart(regsList->ant) : regsList);
};

//Add a new item at the beginning of the list
reg *addStart(reg *regsList, reg *newItem){
	regsList = navStart(regsList);
	newItem->ant = regsList->ant;
	regsList->ant = newItem;
	newItem->prox = regsList;
	return newItem;
};

//Add a new item at the middle of the list
reg *addMiddle(reg *regsList, reg *newItem){
	newItem->prox = regsList->prox;
	regsList->prox != NULL ? regsList->prox->ant = newItem : 0;
	newItem->ant = regsList;
	regsList->prox = newItem;
	return navStart(regsList);
};

//Add a new item to the end of the list
reg *addEnd(reg *regsList, reg *newItem){
	regsList = navEnd(regsList);
	newItem->ant = regsList;
	newItem->prox = regsList->prox;
	regsList->prox = newItem;
	return navStart(regsList);
};

//Remove the first item at the beginning of the list
reg *remStart(reg *regsList){
	regsList = navStart(regsList);
	reg *temp = regsList->prox;
	(temp != NULL) ? (temp->ant = regsList->ant) : 0;
	free(regsList);
	return temp;
};

//Remove an item in the middle of the list
reg *remMiddle(reg *regsList){
	reg *temp = navStart(regsList);
	if(regsList->ant != NULL && regsList->prox != NULL){
		regsList->ant->prox = regsList->prox;
		regsList->prox->ant = regsList->ant;
		free(regsList);
	}
	return temp;
};

//Remove the last item at the end of the list
reg *remEnd(reg *regsList){
	regsList = navEnd(regsList);
	reg *temp = navStart(regsList);
	(regsList->ant != NULL) ? (regsList->ant->prox = regsList->prox) : 0;
	free(regsList);
	return temp;
};
