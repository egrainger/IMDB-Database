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
  fptr = fopen(userFile, "w+"); 


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
  
  while (userChoiceProper != 'e'){
    switch (userChoiceProper) {

    case 'a':
      printf("ADD\n");
      char typeOwned[8];
      char purchased[11];

      //Get proper user search title
      /*char search[250]; 
      printf("Please type the title of the movie you wish to add to your library. Omit an initial article such as 'The,' 'A,' or 'An':\t"); 
      scanf("%[^\n]s", search);       //Scan in movie title
      printf("%s\n", search); 
      removeSubstr(search, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
      printf("%s\n", search);
      removeSubstr(search, "a ");
      printf("%s\n", search);
      removeSubstr(search, "an ");
      printf("%s\n", search);

      //Search the database avl tree
      printf("searching for: %s\n", search); 
      display_avl(find(search, HEAD_DB));
      */
      printf("When did you purchase this movie? Please respond in this format: MM/DD/YYYY.\t");
      scanf("%s", purchased);
      printf("Purchased: %s", purchased);
      
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
      printf("If you typed in an incorrect response, the format of the movie will default to digital copy.\n"
      break;
    
    case 'u':
      printf("UPDATE\n"); 
      break;
    
    case 'r':
      printf("READ\n");
      break;
    
    case 'd':
      printf("DELETE\n");
      break;
    
    case 'h':
      printf("HELP\n");
      help();
      break;

    case 'e':
      return 0; 
    
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
