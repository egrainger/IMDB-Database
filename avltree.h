/* Code courtesy of http://www.zentut.com/c-tutorial/c-avl-tree/ */
//Code updated to work with my needs
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#ifndef AVLTREE_H_
#define AVLTREE_H_
 
typedef struct node {
  struct Movie info;    //Want to be able to store necessary info for each movie 
  struct node*  left;
  struct node*  right;
  int      height;  
} node;
 
node* find(char *str, node *t); //find a node based on a user's string input
node* find_min( node *t ); //n/a
node* find_max( node *t ); //n/a
node* insert( struct Movie newMovie, node *t ); //based on struct built create a node to insert into user's avl tree
node *del(node *tTree, char *str); //delete a node from the user's tree based on their string input
void display_avl(node* t); //display the whole avl tree minus format and date (mostly for original database
void display_user(node* t); //display the user's tree including format and date
char* get( node* n ); //n/a
void display_matches(node* t, char *userInput, struct Movie *matches, int *count); //the function that still won't work -_-
void display_userChoice(node *t); //displays retrieved node based on user's text 
void print_to_text(node* t, FILE *userFile); //prints user's final avl tree on exit of program to their .txt file

#endif // AVLTREE_H_
