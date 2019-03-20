#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Help function to remind user of function options
void help (void) {
  printf("This library offers five main functions: add movies, update their information, delete your movies, read your log file, and help.\nTo select one of these options please enter the character associated with your desired function:\n\ta\tadd a movie to your library\n\tu\tupdate the information for a movie in your library currently\n\tr\tread your library\n\td\tdelete a movie from your library.\n\th\tinitial message will remind you of your options.\n");
}

//Error message for input formatting issues
void error (void) {
  printf("There is an issue with your input. Please try again. If you need help, please enter in 'h'\n");
  printf("Please enter your input now:\t"); 
}

void exitContinue (void) {
 printf("If you wish to continue, please enter in any of the given character options.\nOtherwise, enter 'e' to exit the program.\t");
} 
