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

	record *test = new_record_overloaded(1,26.74,new_datetime(),"conteudo aleatorio para serializacao de dados",5,"ab yuu27 129921 fdkjfdkjfkdjfkdfj");
	test->add(test,new_record_overloaded(2,105.98,new_datetime(),"alguma coisa para preencher",15,"eita lasqeura"));
	test->add(test,new_record_overloaded(3,49.67,new_datetime(),"ola teste ops",67,"lorem ipsum"));
	test->add(test,new_record_overloaded(4,26.74,new_datetime(),"conteudo aleatorio para serializacao de dados",12,"ab yuu27 129921 fdkjfdkjfkdjfkdfj"));
	
	
	// record *percursor = test;
	// for (percursor = test; percursor != NULL; percursor = percursor->next)
	// {
	// 	percursor->show(percursor);
	// }
	
		// printf("%s",string_join(INDEFINITE_LENGTH,EMPTY_SEPARATOR,
        // ( test->prev == NULL ? "[{" : ",{"),
        // "\"Id\":","id",
        // ",\"Description\":\"",test->description,
        // "\",\"Category_id\":","category",
        // ",\"Details\":\"",test->details,
        // "\",\"Datetime\":\"",test->datetime.format_string(test->datetime,DATABASE_UTC),
        // "\",\"Value\":","value",
        // (test->next == NULL ? "}]" : "}"),NULL));

	// // ------------------ área para teste
	// char *json_result = (char*)malloc(sizeof(char)*2);
    // strcpy(json_result,"\0");
    // record *element = navigate_to_start(test);
        
    // for(element; element != NULL; element = element->next)
    // {
    //     int size_id = snprintf( NULL, 0, "%li", element->id ) + 1;
    //     int size_category = snprintf( NULL, 0, "%li", element->category_id ) + 1;
    //     int size_value = snprintf( NULL, 0, "%Lf", element->value ) + 1;
    //     size_t size = DATETIME_MAX_LENGTH + MAX_DESCRIPTION + MAX_DETAILS + size_id + size_category + size_value + strlen(json_result) + 77;
        
    //     char *id = (char*)malloc(sizeof(char)*size_id);
    //     char *category = (char*)malloc(sizeof(char)*size_category);
    //     char *value = (char*)malloc(sizeof(char)*size_value);

    //     sprintf(id, "%li", element->id);
    //     id[strlen(id)] = '\0';
    //     sprintf(category, "%li", element->category_id);
    //     category[strlen(category)] = '\0';
    //     sprintf(value, "%Lf", element->value);
    //     value[strlen(value)] = '\0';
        
    //     char* aux = json_result;
    //     json_result = (char*)malloc(sizeof(char)*size);
    //     strcpy(json_result,aux);

    //     strcat(json_result,string_join(INDEFINITE_LENGTH,EMPTY_SEPARATOR,
    //     ( element->prev == NULL ? "[{" : ",{"),
    //     "\"Id\":",id,
    //     ",\"Description\":\"",element->description,
    //     "\",\"Category_id\":",category,
    //     ",\"Details\":\"",element->details,
    //     "\",\"Datetime\":\"",element->datetime.format_string(element->datetime,DATABASE_UTC),
    //     "\",\"Value\":",value,
    //     (element->next == NULL ? "}]" : "}"),NULL));
    
    //     free(id);
    //     free(aux);
    //     free(value);
    //     free(category);

    // }
	// // ------------------ área para teste

	char *json_result = serialize_to_json(test);
	printf("json: \n%s",json_result);
	

	write_file(json_result,WRITE,"./struct_serializada.json");
	
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

