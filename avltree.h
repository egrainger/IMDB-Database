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
 
void dispose(node* t);
//struct Movie find(char *str, node *t );
node* find(char *str, node *t); 
node* find_min( node *t );
node* find_max( node *t );
node* insert( struct Movie newMovie, node *t );
node* delete( char *str, node *t );
void display_avl(node* t);
char* get( node* n );

#endif // AVLTREE_H_
