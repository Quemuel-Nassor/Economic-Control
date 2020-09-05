/*
	This library contains functions to display de header of program
	and to display program menu options 
*/

//Dependencies
#include<unistd.h>
#include<stdio.h>

//Function to clean screen
void ClrScr(){
	int i = 0;
     for(i = 0; i < 500; i++){
          printf("\n");
     }
} 

//Function to display program header
void HEADER(){
	
	printf("****************************************************************************************************\n\n");
	printf("****************************************| Economic Control |****************************************\n\n");
	printf("****************************************************************************************************\n\n\n\n");
}

//Custom libraries 
#include"feedLibrary.h"
#include"loadLibrary.h"
#include"toolsLibrary.h"
#include"sortLibrary.h"

//Function to display menu of program
void Menu(reg *regsList,char path[30],FILE *dataBase){
	
	//Local variables
	int option = 0;
	
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
				
	//Loading data from archives for regsList 
	regsList = (loadListFromTxt(regsList,dataBase,path)) == NULL ? (loadListFromJson(regsList,dataBase,path)) == NULL ? newReg() : 0 : (loadListFromTxt(regsList,dataBase,path));
	ClrScr();
	HEADER();
	
	//Displays menu options and informations
	printf("Active Database: %c%s%c\n\n",34,path,34);
	printf("Select an option:");
	printf("\n\n1 - New register \n2 - View registers \n3 - Change register \n4 - Switch data base \n5 - About \n6 - Exit\n\n");
	
	//Selection menu
	setbuf(stdin,NULL);
	switch((getchar()-48)){
		
		case 1:{				
			
			//Add a new register in the list
			ClrScr();
			if(strcmp(regsList->date,"") != 0){
				
				addEnd(regsList,newReg());
				dataFeed(navEnd(regsList));
				
			}else{
				
				dataFeed(regsList);
			}
			
			//Sort by ascending date before writing to file
			regsList = orderByDate(regsList);
			
			//Write regsList in file
			saveListAsJson(regsList,dataBase,path);
			saveListAsTxt(regsList,dataBase,path);
			
			//Return to menu
			Menu(regsList,path,dataBase);
			break;
		}
		
		case 2:{
			
			//Validating regList
			if(regsList != NULL && strcmp(regsList->date,"") != 0){
				
				//Loop of submenu
				do{				
					//Displaying regsList
					ClrScr();
					HEADER();
					showRecords(orderByDate(regsList));
					
					//Diplaying options
					printf("\n\n   Select an option: ");
					printf("\n\n   1 - Order by Date \n   2 - Order by Id  \n   3 - Order by Value \n   4 - Return to menu \n\n");
					
					//Selection menu
					setbuf(stdin,NULL);
					switch((getchar()-48)){
						
						case 1:{
							
							//Sort by ascending date
							regsList = orderByDate(regsList);
							break;
						}
						
						case 2:{
							
							//Sort by ascending id
							regsList = orderById(regsList);
							break;
						}
						
						case 3: {
							
							//Sort by ascending value
							regsList = orderByValue(regsList);
							break;
						}
						
						case 4:{
							
							option = 4;
							break;
						}
						
						default:{
							
							//Feedback default
							ClrScr();
							printf("\n\n\n\t\t\t\tInvalid option!");
							sleep (1);
							break;
						}
					}
					
				}while(option != 4);
				
			}else{

				//Feedback if regsList is empty
				ClrScr();
				printf("\n\n\n\t\t\t\tNo exists records to display!!!");
				sleep (2);
				
			}
			
			//Return to menu
			Menu(regsList,path,dataBase);
			break;
		}
		
		case 3:{
			ClrScr();
			HEADER();
			
			//Edit a register of regsList
			editRecord(regsList);
			
			//Sort by ascending date before writing to file
			orderByDate(regsList);
			
			//Write regsList in file
			saveListAsJson(regsList,dataBase,path);
			saveListAsTxt(regsList,dataBase,path);

			//Return to menu
			Menu(regsList,path,dataBase);
			break;
		}
		
		case 4:{
			
			//Switch data base
			switchDataBase();

			//Return to menu
			Menu(regsList,path,dataBase);
			break;
		}
			
		case 5:{
			
			//About
			ClrScr();
			HEADER();
			printf("This software is free and intended for personal use.\nIts use in business environments is not recommended for security reasons !!!\n\n");
			printf("Developer: Quemuel Alves Nassor\n\nContact or support: quemuelalp@hotmail.com\n\n");
			setbuf(stdin,NULL);
			getchar();
			
			//Return to menu
			Menu(regsList,path,dataBase);
			break;
			
		}
		
		case 6:{
			
			//Exit of program
			ClrScr();
			exit(0);
			break;
		}
			
		default:{
			
			//Feedback default
			ClrScr();
			printf("\n\n\n\t\t\t\tInvalid option!");
			sleep(1);
			
			//Return to menu
			Menu(regsList,path,dataBase);
			break;
		}
	}
		
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
}
