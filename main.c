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

static int counter = 1; 

int main (void) {
 
  //Initialize avl tree for database
  node *HEAD_DB = NULL; 
  HEAD_DB = parsedatabase(HEAD_DB); 

  //Double check to make sure database tree isn't empty
  if (HEAD_DB == NULL)
    printf("HEAD_DB is NULL!\n");
  
  //Initialize avl tree for user
  node *HEAD_USER = NULL; 
  
  //Want an array to hold matches found by the display_matches function
  struct Movie empty = {0}; 
  struct Movie match[30] = {empty};
  
  //Welcome message; obtain userID
  printf("Welcome to your movie library.\nTo begin, please enter in your userID in the format of 'firstname_lastname' to avoid duplicate logs.\n");
  char userID[50];
  scanf("%s", userID);
  printf("\nHello %s!\n", userID); 
  
  //Open file for user library
  FILE *fptr;
  char userFile[55];
  strcpy(userFile, strcat(userID, ".txt"));
  if((fptr = fopen(userFile, "r")) != NULL)
    HEAD_USER = parseUserFile(HEAD_USER, fptr);
  fclose(fptr); 
  
  //Display user function choices.
  printf("This library offers six main functions: add movies, update information, delete movies, read your library, help, and exit.\nTo select one of these options please enter the character associated with your desired function:\n\n\ta\tadd a movie to your library\n\tu\tupdate the information for a movie in your library currently\n\tr\tretrieve a particular movie's info from your library\n\td\tdelete a movie from your library.\n\th\tinitial message will remind you of your options\n\te\texit the program.\n\n\nPlease type in a single character for your choice:\t");
  
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
      struct Movie userMov; 
      char search[250];

      //Get proper user search title 
      printf("Please type the title of the movie you wish to add to your library. Omit an initial article such as 'The,' 'A,' or 'An':\n"); 
      getchar();  //Flush the \n out of the buffer 
      scanf("%[^\n]s",search);//Scan in movie title

      //Clean up user input
      strlwr(search);                   //All lowercase
      removeSubstr(search, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
      removeSubstr(search, "a ");
      removeSubstr(search, "an "); 
      
      //Search the database avl tree
      printf("Searching for: %s\n", search); 

      //Make sure match array is clear
      for (int i = 0; i <= 30; i++) {
	match[i] = empty;
      }

      //Find top 30 best matches
      display_matches(find(search, HEAD_DB), search, match);
      counter = 1; 
      
      //Print the array with the top thirty matches 
      printf("Match is filled with this: \n");
      for (int x = 0; x <= 30; x++){
	printf("%d\t%s\n", x, match[x].Title);  
      }

      //Have the user pick which movie they wish to add to their log
      printf("Please enter a number 1 - 30 which matches the movie you wish to add to your database.\nPlease note there are only 30 titles available from which you can choose.\nIf none of these titles match your desired movie. Please enter 0, and narrow down your search title. If your input is not a value 1-30 or '0' it will default to escaping\n");
 
      //Read user choice from stdin
      int pickOne;
      scanf("%d", &pickOne);
      printf("Pick: %d\n", pickOne); 
      
      //Leave case a if instructions were not followed
      if (pickOne == 0 || pickOne > 30 ){
	printf("None of the options were correct.\n"); 
	break;
      }

      //Input is valid so add basic movie info to struct
      else {
	strcpy(userMov.Title, match[pickOne].Title); 
	strcpy(userMov.releaseYear, match[pickOne].releaseYear);
	strcpy(userMov.runtimeMinutes, match[pickOne].runtimeMinutes);
	strcpy(userMov.genres, match[pickOne].genres);
	strcpy(userMov.avlTitle, match[pickOne].avlTitle);
	printf("User: %s\t%s\t%s\t%s\n",userMov.Title, userMov.releaseYear, userMov.runtimeMinutes, userMov.genres);
      }

      //Have user enter when they bought the movie
      printf("When did you purchase this movie? Please respond in this format: MM/DD/YYYY.\t");
      scanf("%s", purchased);
      printf("Purchased: %s", purchased);
      strcpy(userMov.date, purchased);
      
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
      }
      else if (typeOwned[0] == 'v'){
	strcpy(typeOwned, "DVD");
      }
      else {
	strcpy(typeOwned, "Digital");
      }

      printf("If you typed in an incorrect response, the format of the movie will default to digital copy.\n");
      strcpy(userMov.format, typeOwned);
      
      HEAD_USER = insert(userMov, HEAD_USER); 
      
      break;
       
	
      /*This case deals with updating an entry in the user's file*/
      case 'u':
	printf("UPDATE\n");
	node *found;
	
	//Get proper user search title 
	printf("Please type the exact title of the movie you wish to add to your library. Omit an initial article such as 'The,' 'A,' or 'An':\n"); 
	getchar();  //Flush the \n out of the buffer 
	scanf("%[^\n]s",search);//Scan in movie title
	
	//Clean up user input
	strlwr(search);                   //All lowercase
	removeSubstr(search, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
	removeSubstr(search, "a ");
	removeSubstr(search, "an "); 
	
	//Search the database avl tree
	printf("Searching for: %s\n", search); 
	
	//Find top 30 best matches 
	found = find(search, HEAD_USER);
	if (strcmp(found->info.avlTitle, search) != 0 || strlen(found->info.avlTitle) != strlen(search)) {
	  printf("Please try update again and type the exact title\n."); 
	  break; 
    }
	printf("To update date of purchase type 'd'. To update format owned type 'f'. To update both, type 'b'. Please enter your input: \t");
	//Read user choice from stdin
	scanf("%s", userChoice);
	
	//Make sure that input is an actual choice
	while (userChoice[1] != '\0') {    //The input is not a single character
	  error();
	  scanf("%s", userChoice);       //Scan in new input
	}
	userChoiceProper = userChoice[0];
	
	switch (userChoiceProper) {
	  
	case 'd':
	  printf("When did you purchase this movie? Please respond in this format: MM/DD/YYYY.\t");
	  scanf("%s", purchased);
	  strcpy(found->info.date, purchased);  
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
	  }
	  else if (typeOwned[0] == 'v'){
	    strcpy(typeOwned, "DVD");
	  }
	  else {
	    strcpy(typeOwned, "Digital");
	  }
	  strcpy(found->info.format, typeOwned); 
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
	  }
	  else if (typeOwned[0] == 'v'){
	    strcpy(typeOwned, "DVD");
	  }
	  else {
	    strcpy(typeOwned, "Digital");
	  }
	   strcpy(found->info.date, purchased);
	   strcpy(found->info.format, typeOwned);
	  printf("If you typed in an incorrect response, the format of the movie will default to digital copy.\n");   
	  break;
	  
	default:
	  printf("Your response is not valid. You will have to try update again.\n");      
	  break; 
	}
	break;
	
	/*This case allows the reader to view a node in their current file*/

    case 'r':
      printf("READ\n");
      
      //Get proper user search title
      printf("Please type the exact title of the movie you wish to read from your library. Omit an initial article such as 'The,' 'A,' or 'An':\n");
      getchar();  //Flush the \n out of the buffer
      scanf("%[^\n]s",search);//Scan in movie title

      //Clean up user input
      strlwr(search);                   //All lowercase
      removeSubstr(search, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
      removeSubstr(search, "a ");
      removeSubstr(search, "an ");

      //Find the one match
      display_userChoice(find(search,HEAD_USER), search);
      
      break;
      
      /*This case allows the user to delete a movie from their file*/
    case 'd':
      printf("DELETE\n");

      //Get proper user search title 
      printf("Please type the title of the movie you wish to delete from your library. Omit an initial article such as 'The,' 'A,' or 'An':\n"); 
      getchar();  //Flush the \n out of the buffer 
      scanf("%[^\n]s",search);//Scan in movie title

      //Clean up user input
      strlwr(search);                   //All lowercase
      removeSubstr(search, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
      removeSubstr(search, "a ");
      removeSubstr(search, "an ");
      
      delete(HEAD_USER, search);
      break;
      
      /*This case prints a help message*/
    case 'h':
      printf("HELP\n");
      help();
      break;
      
      /*This case occurs when the user's input does not match any of the other cases*/
    default:  
      printf("INVALID INPUT\n"); 
      break; 
    }
    
    //Scan for new input
    exitContinue();
    scanf("%s", userChoice);
    while (userChoice[1] != '\0') {
      error();
      scanf("%s", userChoice);
    }
    userChoiceProper = userChoice[0];
  }

  //Write final user tree to its text file 
  fptr = fopen(userFile, "w");
  print_to_text(HEAD_USER, fptr); 
  fclose(fptr);
  
  printf("\nEXIT\n");
  return 0;
}
