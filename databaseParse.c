#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "databaseParse.h"

int parsedatabase (void) { 
  char primaryTitle[250];
  char releaseYear[5];
  char runtimeMinutes[5];
  char genres[100];
  char line[225];
  char *token;
  int i = 0; 
  
  FILE * movie;
  movie = fopen("movie_records.txt", "r");

  while (fgets(line, sizeof(line), movie) != NULL) {
    token = strtok(line, "\t");    //Get first token
    while( token != NULL ) {       // walk through other tokens
      //printf( " %s\n", token);
      switch (i) {
        case 2:
	  strcpy(primaryTitle, token);
	  printf( " %s\n", primaryTitle);
	  break;

        case 5:
	  strcpy(releaseYear, token);
	  printf( " %s\n", releaseYear);
	  break;

        case 7:
	  strcpy(runtimeMinutes, token);
	  printf( " %s\n", runtimeMinutes);
	  break; 

        case 8:
	  strcpy(genres, token);
          printf( " %s\n", genres);
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

return 0;
}


