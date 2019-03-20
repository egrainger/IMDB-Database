/*removeSubstr is courtesy of a nice purpose on https://cboard.cprogramming.com/c-programming/143155-simple-removal-string-string-via-strtok.html*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "databaseParse.h"
#include "structs.h"

void removeSubstr (char *string, char *sub) {
	char *match;
	int len = strlen(sub);
	while ((match = strstr(string, sub))) {
		*match = '\0';
		strcat(string, match+len);
	}
}

int parsedatabase (void) { 
  char line[225];
  char *token;
  int i = 0; 
  struct Movie newMovie; 

  printf("Please wait a moment movie_records.txt is being parsed.\n"); 
  
  FILE * movie;
  if(!(movie = fopen("movie_records.txt", "r"))) {
    printf("movie_records.txt is missing from your directory.\nPlease follow the instructions in the README to create this file then rerun this script.\n");
    return 2;
  }
  
  while (fgets(line, sizeof(line), movie) != NULL) {
    token = strtok(line, "\t");    //Get first token
    while( token != NULL ) {       // walk through other tokens
      switch (i) {
        case 2:
	  strcpy(newMovie.Title, token);  //Maintain copy of original title for user's records
 	  strlwr(token);                 //Avoids weird user input with incorrect capitalization
          removeSubstr(token, "the ");    //Avoid missing articles: 'the ', 'an ', and 'a ' which we can assume to have a space following them always due to English standards
          removeSubstr(token, "a ");
          removeSubstr(token, "an ");
	  strcpy(newMovie.avlTitle, token);
	  printf(" %s\n", newMovie.avlTitle); //Have a copy of title to more easily search: all lower case and no articles. 
	  break;

        case 5:
	  strcpy(newMovie.releaseYear, token);
	  break;

        case 7:
          strcpy(newMovie.runtimeMinutes, token);
	  break; 

        case 8:
	  strcpy(newMovie.genres, token);
	  break; 

        default:
	  break;
      }
      i++; 
      token = strtok(NULL, "\t");
      
   }
    i = 0; 
}
fclose(movie);

 printf("The database has been fully parsed. Thank you for you patience.\n"); 
 
return 0;
}


