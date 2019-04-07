/*Lowercase function*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

void lower(char *str) { 
  int i = 0;
	
   while( str[i] ) {
      str[i] = tolower(str[i]);
      i++;
   }
   return;
}


