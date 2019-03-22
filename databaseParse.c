/*removeSubstr is courtesy of a nice purpose on https://cboard.cprogramming.com/c-programming/143155-simple-removal-string-string-via-strtok.html*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "databaseParse.h"
#include "avltree.h"
#include "structs.h"

/*This function's purpose is to help remove articles from my titles for ease of comparison*/
void removeSubstr (char *string, char *sub) { //string is my title and sub is the article which I want to remove
  char *match;
  int len = strlen(sub);
  while ((match = strstr(string, sub))) {
    *match = '\0';
    strcat(string, match+len);
  }
}

/*This function's purpose is to parse the database and add each movie to an AVL tree for storage and lookup*/
node* parsedatabase (node *tree) { 
  char line[225];
  char *token; //This stores each string delimited by a tab
  int i = 0; //Used to track which column of the file data the parsing is on. 
  struct Movie newMovie; //This will be sent to the AVL tree to be stored

  printf("\nPlease wait a moment movie_records.txt is being parsed.\n"); //Let the user know to be patient
  
  FILE * movie;
  movie = fopen("movie_records.txt", "r");

  while (fgets(line, sizeof(line), movie) != NULL) { //Read in the file line by line for each movie object
    token = strtok(line, "\t");    //Get first token
    while( token != NULL ) {       // walk through other tokens
      switch (i) {
        case 2:
	  strcpy(newMovie.Title, token);  //Maintain copy of original title for user's records
 	  strlwr(token);                 //Avoids weird user input with incorrect capitalization
          removeSubstr(token, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
          removeSubstr(token, "a ");
          removeSubstr(token, "an ");
	  strcpy(newMovie.avlTitle, token); //Store the modified title which is all lowercase with no articles
	  break;

        case 5:
	  strcpy(newMovie.releaseYear, token); //Store the release year
	  break;

        case 7:
          strcpy(newMovie.runtimeMinutes, token); //Store the runtime in minutes
	  break; 

        case 8:
	  strcpy(newMovie.genres, token);  //Store the genres 
	  break; 

      default: //Just in case weird stuff happens
	  break;
      }
      i++; //increment after each column 
      token = strtok(NULL, "\t"); 
      
   }
    i = 0; //reset i value for next movie
    tree = insert(newMovie, tree); //insert the new movie into the database's AVL tree
  }
  //display_avl(tree);
  if (tree == NULL)
    printf("Tree is NULL\n");
  fclose(movie); //close movie_records.txt once finished
  
  printf("The database has been fully parsed. Thank you for you patience.\n\n");
  return tree;
}


