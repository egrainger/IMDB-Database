/*Project: Movie Database 
  Creator: Emma Grainger
  Overview: Create and maintain a personal user library of movie titles from a compiled database. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "databaseParse.h"
#include "structs.h"
#include "messages.h"
#include "avltree.h"

int main (void) {
  
  //Initialize avl tree for database
  node *HEAD_DB = NULL; 
  HEAD_DB = parsedatabase(HEAD_DB); 

  //Double check to make sure database tree isn't empty
  if (HEAD_DB == NULL)
    printf("HEAD_DB is NULL!\n");
  
  //Initialize avl tree for user
  node *HEAD_USER = NULL; 
  
  //Welcome message; obtain userID
  printf("Welcome to your movie library.\nTo begin, please enter in your userID in the format of 'firstname_lastname' to avoid duplicate logs.\n");
  char userID[50];
  scanf("%s", userID);
  printf("\nHello %s!\n", userID); 
  
  //Open file for user library
  FILE *fptr;
  char userFile[55];
  strcpy(userFile, strcat(userID, ".txt"));
  fptr = fopen(userFile, "w"); 
  
  
  //Display user function choices.
  printf("This library offers six main functions: add movies, update information, delete movies, read your library, help, and exit.\nTo select one of these options please enter the character associated with your desired function:\n\n\ta\tadd a movie to your library\n\tu\tupdate the information for a movie in your library currently\n\tr\tread your library\n\td\tdelete a movie from your library.\n\th\tinitial message will remind you of your options\n\te\texit the program.\n\n\nPlease type in a single character for your choice:\t");
  
  //Read user choice from stdin
  char userChoice[20];
  scanf("%s", userChoice);
  
  //Make sure that input is an actual choice
  while (userChoice[1] != '\0') {    //The input is not a single character
    error();
    scanf("%s", userChoice);       //Scan in new input
  }

  //Identify the single character for function choice
  char userChoiceProper;
  userChoiceProper = userChoice[0]; 

  char typeOwned[8];
  char purchased[11];
  
  while (userChoiceProper != 'e'){
    switch (userChoiceProper) {
      
      /*This case deals with adding a new entry to the user's file*/
    case 'a':
      printf("ADD\n");

      char search[250];
      //Get proper user search title 
      printf("Please type the title of the movie you wish to add to your library. Omit an initial article such as 'The,' 'A,' or 'An':\n"); 
      getchar();  //Flush the \n out of the buffer 
      scanf("%[^\n]s",search);//Scan in movie title
      printf("FOUND: %s\n", search); 
      removeSubstr(search, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
      //printf("%s\n", search);
      removeSubstr(search, "a ");
      //printf("%s\n", search);
      removeSubstr(search, "an ");
      //printf("%s\n", search);
      strlwr(search); 
      
      //Search the database avl tree
      printf("searching for: %s\n", search); 
      display_matches(find(search, HEAD_DB), search);

      //Have user enter when they bought the movie
      printf("When did you purchase this movie? Please respond in this format: MM/DD/YYYY.\t");
      scanf("%s", purchased);
      printf("Purchased: %s", purchased);

      //Have user enter what type of format their version of the movie is in 
      printf("\nWhat format do you own? To answer please type 'b' for bluray, 'v' for dvd, or 'd' for digital:\t");
      //Read user choice from stdin
      scanf("%s", typeOwned);
      
      //Make sure that input is an actual choice
      while (typeOwned[1] != '\0') {    //The input is not a single character
	error();
	scanf("%s", typeOwned);       //Scan in new input
      }
      if (typeOwned[0] == 'b'){
	strcpy(typeOwned, "Bluray");
	//printf("%s\n", typeOwned);
      }
      else if (typeOwned[0] == 'v'){
	strcpy(typeOwned, "DVD");
        //printf("%s\n", typeOwned);
      }
      else {
	strcpy(typeOwned, "Digital");
        //printf("%s\n", typeOwned);
      }
      printf("If you typed in an incorrect response, the format of the movie will default to digital copy.\n");
       
      break;
       
	
      /*This case deals with updating an entry in the user's file*/
      case 'u':
	     printf("UPDATE\n");

	     char choice[3];
	     char choiceProper;
	     
	     printf("To update date of purchase type 'd'. To update format owned type 'f'. To update both, type 'b'. Please enter your input: \t");
	     //Read user choice from stdin
	     scanf("%s", choice);

	     //Make sure that input is an actual choice
	     while (choice[1] != '\0') {    //The input is not a single character
	       error();
	       scanf("%s", choice);       //Scan in new input
	     }
	     choiceProper = choice[0];

	     switch (choiceProper) {

	     case 'd':
	       printf("When did you purchase this movie? Please respond in this format: MM/DD/YYYY.\t");
	       scanf("%s", purchased);
	       printf("Purchased: %s", purchased);
	       break;
	       
	     case 'f':
	       printf("\nWhat format do you own? To answer please type 'b' for bluray, 'v' for dvd, or 'd' for digital:\t");
	       //Read user choice from stdin
	       scanf("%s", typeOwned);
	       
	       //Make sure that input is an actual choice
	       while (typeOwned[1] != '\0') {    //The input is not a single character
		 error();
		 scanf("%s", typeOwned);       //Scan in new input
	       }
	       if (typeOwned[0] == 'b'){
		 strcpy(typeOwned, "Bluray");
		 //printf("%s\n", typeOwned);
	       }
	       else if (typeOwned[0] == 'v'){
		 strcpy(typeOwned, "DVD");
		 //printf("%s\n", typeOwned);
	       }
	       else {
		 strcpy(typeOwned, "Digital");
		 //printf("%s\n", typeOwned);
	       }
	       printf("If you typed in an incorrect response, the format of the movie will default to digital copy.\n");
	       break;
		      
	       case 'b':
	       //New purchase date
	        printf("When did you purchase this movie? Please respond in this format: MM/DD/YYYY.\t");
	        scanf("%s", purchased);
	        printf("Purchased: %s", purchased);

	       //New format
	      printf("\nWhat format do you own? To answer please type 'b' for bluray, 'v' for dvd, or 'd' for digital:\t");
	      //Read user choice from stdin
	      scanf("%s", typeOwned);
	      
	      //Make sure that input is an actual choice
	      while (typeOwned[1] != '\0') {    //The input is not a single character
		error();
		scanf("%s", typeOwned);       //Scan in new input
	      }
	      if (typeOwned[0] == 'b'){
		strcpy(typeOwned, "Bluray");
		//printf("%s\n", typeOwned);
	      }
	      else if (typeOwned[0] == 'v'){
		strcpy(typeOwned, "DVD");
		//printf("%s\n", typeOwned);
	      }
	      else {
		strcpy(typeOwned, "Digital");
		//printf("%s\n", typeOwned);
	      }
	      printf("If you typed in an incorrect response, the format of the movie will default to digital copy.\n");   
	       break;

	     default:
	       printf("Your response is not valid. You will have to try update again.\n");      
	       break; 
	     }
	     break;

      /*This case allows the reader to view their current file*/
      case 'r':
        printf("READ\n");
	display_avl(HEAD_USER); 
      break;
	     
     /*This case allows the user to delete a movie from their file*/
     case 'd':
       printf("DELETE\n");
     break;
	     





     

     /*This case prints a help message*/
     case 'h':
       printf("HELP\n");
       help();
     break;

     /*This case allows the user to exit the program*/
     case 'e':
       return 0; 
	     
     /*This case occurs when the user's input does not match any of the other cases*/
     default:  
       printf("INVALID INPUT\n"); 
     break; 
      }
	
   //Scan for new input
   //    printf("If you wish to continue please enter in any of the given character options. Otherwise, please enter 'e' to exit the program.\t");
     exitContinue();
     scanf("%s", userChoice);
     while (userChoice[1] != '\0') {
       error();
       scanf("%s", userChoice);
      }
      userChoiceProper = userChoice[0];
    }
    
   fclose(fptr); 
   printf("\nEXIT\n");
   return 0;
 }
