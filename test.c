/*
	This mainFile contains library additions and the basic 
	program execution and verification environment
*/

//Dependencies
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>

//Custom libraries 
#include <record.h>
#include <dir_mgmt.h>

//Constants
#define LIN 50
#define COL 50

//Global variables 
char basePath[30] = "Database";
char yearsPath[25];
char categoryList[LIN][COL];
int sizeOfCategoryList;
FILE *dataBase;
FILE *yearList;

//Funtion to create directories
void ___mkdir (char *path);

//Defines '\' or '/' and mkdir on unix/windows environtments
#ifdef __unix__         
    
	const char *DIRECTORY_SEPARATOR_CHAR = "/";
	
	void ___mkdir (char *path){
		mkdir(path,0700);
	}

#elif defined(_WIN32) || defined(WIN32) 

	const char *DIRECTORY_SEPARATOR_CHAR = "\\";
	
	void ___mkdir (char *path){
   		mkdir(path);
	}

#endif

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
#include"loadLibrary.h"
#include"menu.h"

//Extern declarations

//Main function
int main(void){
	
	// checkDatabase2();

	record *test = new_record_overloaded(10,26.74,new_datetime(),"conteudo aleatorio para serializacao de dados",5,"ab yuu27 129921 fdkjfdkjfkdjfkdfj");
	test->add(test,new_record_overloaded(20,105.98,new_datetime(),"alguma coisa para preencher",15,"eita lasqeura"));
	test->add(test,new_record_overloaded(30,49.67,new_datetime(),"ola teste ops",67,"lorem ipsum"));
	test->add(test,new_record_overloaded(40,15.24,new_datetime(),"conteudo aleatorio para serializacao de dados",12,"ab yuu27 129921 fdkjfdkjfkdjfkdfj"));
	
	char *json_result = serialize_to_json(test);
		

	write_file(json_result,WRITE,string_join(INDEFINITE_LENGTH,DIR_SEPARATOR_CHR,".","struct_serializada.json",NULL));
	
	clean_list(test);
	
	// //Call checks data base function
	// checkDatabase();
	
	// //Load category list
	// loadConfig(categoryList);
	// record *list = new_record();
	// //Call menu program function
	// Menu(list,basePath,dataBase);

	return(0);
}

