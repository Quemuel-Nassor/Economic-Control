void HEADER(){
	
	printf("****************************************************************************************************\n\n");
	printf("****************************************| Economic Control |****************************************\n\n");
	printf("****************************************************************************************************\n\n\n\n");
}

//Menu function
void Menu(list_cad *main_list,FILE *data_base){
		
		//submenu sorting options
		char submenu[220] ="\n\n  ================================\n |   1 - Ordenar por Data         |\n |   2 - Ordenar por Valor        |\n |   3 - Ordenar por Categoria    |\n |   ESC - Retornar ao menu       |\n  ================================\n";
		
		//frees memory allocated by main_list
		deallocate_list(main_list);
					
		//read data from files for main_list and sort for date
		load_list(main_list,data_base,month,year);
		
		//define color green
		system("COLOR 0A");
		
		//displays menu options
		system("cls");
		HEADER();
		printf("Selecione uma op��o:\n\n1 - Novo cadastro \n2 - Exibir cadastros \n3 - Alterar cadastro\n4 - Alternar base de dados\n5 - Sobre\n6 - Sair");
		int option = -1;
		
		//selection menu
		setbuf(stdin,NULL);
		switch(getch()-48){
			
			case 1:{				
				system("cls");
				//concatenate a new record in the list
				add_new(category,main_list,"",Date);
				
				//sort for date before burn in file
				ord_date(main_list);
				
				//writes main_list in file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);	
				break;
			}
			
			case 2:{
				
				//check if main_list is empty
				if(main_list->prox == NULL){
					
					//define color red
					system("COLOR 0C");
			
					//feedback if main_list is empty
					system("cls");
					printf("\n\n\n\t\t\t\tN�o existem cadastros na main_lista!!!");
					sleep (2);
					
					//Displaying regsList
					ClrScr();
					HEADER();
					showRecords(orderByDate(regsList));
					
					//Loop of submenu
					do{
						
						//define color green
						system("COLOR 0A");
						
						//displaying main_list
						system("cls");
						HEADER();
						ord_date(main_list);
						show_records(main_list);
						printf("%s",submenu);
						
						//Sort by ascending date
						regsList = orderByDate(regsList);
						
					}else if(option == 2){
					
						//Sort by ascending id
						regsList = orderById(regsList);
						
					}else if(option == 3){
						
						//Sort by ascending value
						regsList = orderByValue(regsList);
					
					}
					
					if(option != 1 && option != 2 && option != 4 && option !=3){
						
						//Feedback default
						ClrScr();
						printf("\n\n\n\t\t\t\tInvalid option!");
						sleep (1);
						
						if(option != 1 && option != 2 && option != -21 && option !=3){
							
							//define color red
							system("COLOR 0C");
							
							//feedback default
							system("cls");
							printf("\n\n\n\t\t\t\tOp��o inv�lida!");
							sleep (1);
							
						}
					}while(option != -21);
				}
				Menu(main_list,data_base);
				break;
			}
			
			case 3:{
				system("cls");
				HEADER();
				
			}else{
				
				//sort for date before burn in file
				ord_date(main_list);
				
				//writes list in file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);		
				break;
			}
			
			case 4:{
				
				system("cls");
				HEADER();	
							
				//selects other periods to load in main_file
				show_data_base(month,year,"",files);
				Menu(main_list,data_base);				
				break;
			}
				
			case 5:{
				
				//about
				system("cls");
				HEADER();
				printf("Este software � gratuito e destinado para uso pessoal.\nSeu uso em ambientes empresariais n�o � recomendado por quest�es de seguran�a!!!\n\n");
				printf("Desenvolvedor: Quemuel Alves Nassor\n\nContato ou suporte: quemuelalp@hotmail.com\n\nVers�o: 1.0.2");
				setbuf(stdin,NULL);
				getch();
				Menu(main_list,data_base);
				break;
				
			}
			
			case 6:{
				
				//exit of program
				system("cls");
				exit(0);
				break;
			}
				
			default:
				
				//define color red
				system("COLOR 0C");
				
				//feedback default
				system("cls");
				printf("\n\n\n\t\t\t\tOp��o inv�lida!");
				sleep(1);
				Menu(main_list,data_base);
		}
		
		case 4:{
			
			//Switch data base
			switchDataBase(path,dataBase);
						
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
			
		default:
			
			//Feedback default
			ClrScr();
			printf("\n\n\n\t\t\t\tInvalid option!");
			sleep(1);
			
			//Return to menu
			Menu(regsList,path,dataBase);
	}
		
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
}
