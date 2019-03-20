#include <stdio.h>
#include <stdlib.h>

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

  FILE * movie;
  movie = fopen("movie_records.txt", "r");

  while (fgets(line, sizeof(line), movie) != NULL) {
  sscanf(line, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]", tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres);
  printf("%s\t%s\t%s\t%s\t%s\t", titleType, primaryTitle, startYear, runtimeMinutes, genres);
  tconst[0] = '\0';
  titleType[0] = '\0';
  primaryTitle[0] = '\0';
  originalTitle[0] = '\0';
  isAdult[0] = '\0';
  startYear[0] = '\0';
  endYear[0] = '\0';
  runtimeMinutes[0] = '\0';
  genres[0] = '\0';
  }


fclose(movie);

return 0;
}


