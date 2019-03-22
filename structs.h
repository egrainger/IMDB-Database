
#ifndef STRUCTS_H_   // Include guard 
#define STRUCTS_H_
  
/*Use as a way to track the movie information and keep it all together*/ 
/*runtimeMinutes and releaseYear are not integers to allow for a single strtok() call which only deals with strings*/
struct Movie {
  char Title[250];
  char releaseYear[5];      
  char runtimeMinutes[5];
  char genres[100];
  char avlTitle[250]; 
};

#endif // STRUCTS_H_

