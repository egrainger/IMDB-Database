#include "avltree.h"
#ifndef PARSEDATABASE_H_   // Include guard 
#define PARSEDATABASE_H_

void removeSubstr (char *string, char *sub); //I use this function primarily to remove articles from user's inputs
node* parsedatabase(node *tree); //reads IMDB database and stores it in an avl tree
node* parseUserFile(node* tree, FILE *file); //reads user's file if it exists and updates the running avl tree if necessary

#endif // PARSEDATABASE_H_
