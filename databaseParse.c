#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "databaseParse.h"
#include "structs.h"

int parsedatabase (void) { 
  char line[225];
  char *token;
  int i = 0; 
  struct Movie newMovie; 

  printf("Please wait a moment movie_records.txt is being parsed.\n"); 
  
  FILE * movie;
  movie = fopen("movie_records.txt", "r");

  while (fgets(line, sizeof(line), movie) != NULL) {
    token = strtok(line, "\t");    //Get first token
    while( token != NULL ) {       // walk through other tokens
      switch (i) {
        case 2:
	  strcpy(newMovie.Title, token);
	  //printf( " %s\n", newMovie.Title);
	  break;

        case 5:
	  strcpy(newMovie.releaseYear, token);
	  //printf( " %s\n", newMovie.releaseYear);
	  break;

        case 7:
          strcpy(newMovie.runtimeMinutes, token);
	  //printf( " %s\n", newMovie.runtimeMinutes);
	  break; 

        case 8:
	  strcpy(newMovie.genres, token);
          //printf( " %s\n", newMovie.genres);
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


