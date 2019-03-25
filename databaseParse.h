#include "avltree.h"
#ifndef PARSEDATABASE_H_   // Include guard 
#define PARSEDATABASE_H_

void removeSubstr (char *string, char *sub); 
node* parsedatabase(node *tree);   
node* parseUserFile(node* tree, FILE *file); 
#endif // PARSEDATABASE_H_
