#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {

  char tconst[20];
  char titleType[50];
  char primaryTitle[50];
  char originalTitle[50];
  char isAdult[4];
  char startYear[5];
  char endYear[5];
  char runtimeMinutes[4];
  char genres[50];

  char line[225];

  char *token; 
  
  FILE * movie;
  movie = fopen("sample.txt", "r");

  while (fgets(line, sizeof(line), movie) != NULL) {
    printf("%s", line); 
    
    /* get the first token */
    token = strtok(line, "\t");
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( " %s\n", token);
      token = strtok(NULL, "\t");
      
   }
  }
fclose(movie);

return 0;
}


