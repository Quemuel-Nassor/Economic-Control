/*
	This library contains functions to display program menu options 
*/

//Dependencies
#include<unistd.h>
#include<stdio.h>

//Custom libraries 
#include"feedLibrary.h"
#include"toolsLibrary.h"
#include"sortLibrary.h"

//Function to display menu of program
void Menu(record *recsList,char path[30],FILE *dataBase){
	
	//Local variables
	int option = 0;
	
	//Clearing the list of records
	clean_list(recsList);
	recsList = new_record();
				
	//Loading data from archives for recsList 
	recsList = (loadListFromTxt(recsList,dataBase,path)) == NULL ? (loadListFromJson(recsList,dataBase,path)) == NULL ? new_record() : 0 : (loadListFromTxt(recsList,dataBase,path));
	ClrScr();
	HEADER();
	
	//Displays menu options and informations
	printf("Active Database: %c%s%c\n\n",34,path,34);
	printf("Select an option:");
	printf("\n\n1 - New records \n2 - View records \n3 - Change records \n4 - Switch data base \n5 - About \n6 - Exit\n\n");
	
	//Selection menu
	setbuf(stdin,NULL);
	switch((getchar()-48)){
		
		case 1:{				
			
			//Add a new records in the list
			ClrScr();
			if(recsList->id != 0){
				
				add_end(recsList,new_record());
				dataFeed(navigate_to_end(recsList));
				
			}else{
				
				dataFeed(recsList);
			}
			
			//Sort by ascending date before writing to file
			// recsList = orderByDate(recsList);
			
			//Write recsList in file
			saveListAsJson(recsList,dataBase,path);
			saveListAsTxt(recsList,dataBase,path);
			
			//Return to menu
			Menu(recsList,path,dataBase);
			break;
		}
		
		case 2:{
			
			//Validating recList
			if(recsList != NULL && recsList->id != 0){
				
				//Loop of submenu
				do{				
					//Displaying recsList
					ClrScr();
					HEADER();
					showRecords(orderById(recsList));
					
					//Diplaying options
					printf("\n\n   Select an option: ");
					printf("\n\n   1 - Order by Date \n   2 - Order by Id  \n   3 - Order by Value \n   4 - Return to menu \n\n");
					
					//Selection menu
					setbuf(stdin,NULL);
					switch((getchar()-48)){
						
						case 1:{
							
							//Sort by ascending date
							// recsList = orderByDate(recsList);
							break;
						}
						
						case 2:{
							
							//Sort by ascending id
							recsList = orderById(recsList);
							break;
						}
						
						case 3: {
							
							//Sort by ascending value
							recsList = orderByValue(recsList);
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

				//Feedback if recsList is empty
				ClrScr();
				printf("\n\n\n\t\t\t\tNo exists records to display!!!");
				sleep (2);
				
			}
			
			//Return to menu
			Menu(recsList,path,dataBase);
			break;
		}
		
		case 3:{
			ClrScr();
			HEADER();
			
			//Edit a records of recsList
			editRecord(recsList);
			
			//Sort by ascending date before writing to file
			// orderByDate(recsList);
			
			//Write recsList in file
			saveListAsJson(recsList,dataBase,path);
			saveListAsTxt(recsList,dataBase,path);

			//Return to menu
			Menu(recsList,path,dataBase);
			break;
		}
		
		case 4:{
			
			//Switch data base
			switchDataBase();

			//Return to menu
			Menu(recsList,path,dataBase);
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
			Menu(recsList,path,dataBase);
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
			Menu(recsList,path,dataBase);
			break;
		}
	}
		
	//Clearing the list of records
	clean_list(recsList);
	recsList = new_record();
}
