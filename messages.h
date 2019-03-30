#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MESSAGES_H_   // Include guard 
#define MESSAGES_H_   

//Help function to remind user of function options
void help (void) {
  printf("\nThis library offers five main functions: add movies, update their information, delete your movies, read your log file, and help.\nTo select one of these options please enter the character associated with your desired function:\n\ta\tadd a movie to your library\n\tu\tupdate the information for a movie in your library currently\n\tr\tread your library\n\td\tdelete a movie from your library.\n\th\tinitial message will remind you of your options.\n");
}

//Error message for input formatting issues
void error (void) {
  printf("\nThere is an issue with your input. Please try again. If you need help, please enter in 'h'\n");
  printf("Please enter your input now:\t"); 
}

void exitContinue (void) {
 printf("\nIf you wish to continue, please enter in any of the given character options. If you need help remembering what those are, please enter in 'h'.\nOtherwise, enter 'e' to exit the program.\t");
} 

#endif // MESSAGES_H_
