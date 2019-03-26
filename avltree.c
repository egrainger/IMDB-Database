/* Code courtesy of http://www.zentut.com/c-tutorial/c-avl-tree/ 
   https://stackoverflow.com/questions/35297364/avl-tree-delete-item-in-c
   Updated to work with my needs
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "databaseParse.h"
#include "structs.h"
#include "avltree.h" 

/*remove all nodes of an AVL tree*/
void dispose(node* t) {
  if( t != NULL )
    {
      dispose( t->left );
      dispose( t->right );
      free( t );
    }
}

/*find a specific node's title in the tree*/
node *find(char *str, node*t){ 
  int len;
  len = strlen(str); //Useful for strncmp() which will be useful for full or partial matches 
    
  if(t == NULL)
    return NULL;

  if(strncmp(str, t->info.avlTitle, len) < 0) //str is less than current node's title
    return find(str, t->left);

  else if(strncmp(str, t->info.avlTitle, len) > 0) //str is greater than current node's title
    return find(str, t->right);

  else
    return t; 
}

/*find minimum node's key*/
node* find_min( node* t ) {
  if( t == NULL )
    return NULL;

  else if( t->left == NULL )
    return t;

  else
    return find_min( t->left );
}
 

/*find maximum node's key*/
node* find_max( node* t ) {
  if( t != NULL )
    while( t->right != NULL )
      t = t->right;
  
  return t;
}


/*get the height of a node*/
static int height( node* n ) {
  if( n == NULL )
    return -1;
    else
      return n->height;
}


/*get maximum value of two integers*/
static int max( int l, int r) {
    return l > r ? l: r;
}


/*perform a rotation between a k2 node and its left child
  note: call single_rotate_with_left only if k2 node has a left child*/
static node* single_rotate_with_left( node* k2 ) {
  node* k1 = NULL;
  
  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  return k1; /* new root */
}


/*perform a rotation between a node (k1) and its right child
  note: call single_rotate_with_right only if the k1 node has a right child*/
static node* single_rotate_with_right( node* k1 ) {
    node* k2;
    
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    
    return k2;  /* New root */
}


/*perform the left-right double rotation, 
  note: call double_rotate_with_left only if k3 node has a left child and k3's left child has a right child */
static node* double_rotate_with_left( node* k3 ) {
  /* Rotate between k1 and k2 */
  k3->left = single_rotate_with_right( k3->left );
  
  /* Rotate between K3 and k2 */
  return single_rotate_with_left( k3 );
}


/*perform the right-left double rotation
  notes: call double_rotate_with_right only if k1 has a right child and k1's right child has a left child*/
static node* double_rotate_with_right( node* k1 ) {
  /* rotate between K3 and k2 */
  k1->right = single_rotate_with_left( k1->right );
  
  /* rotate between k1 and k2 */
  return single_rotate_with_right( k1 );
}


/*insert a new node into the tree*/
node* insert(struct Movie newMovie, node* t ) {
  if( t == NULL )
    {
      /* Create and return a one-node tree */
      t = (node*)malloc(sizeof(node));
      if( t == NULL )
        {
	  fprintf (stderr, "Out of memory!!! (insert)\n");
	  exit(1);
        }
      else
        { //copy all of the input struct's info over into the new node to be added
	  strcpy(t->info.Title, newMovie.Title);    
	  strcpy(t->info.releaseYear ,newMovie.releaseYear);
	  strcpy(t->info.runtimeMinutes ,newMovie.runtimeMinutes);
	  strcpy(t->info.genres ,newMovie.genres);
	  strcpy(t->info.avlTitle ,newMovie.avlTitle);	 
	  t->height = 0;
	  t->left = t->right = NULL;
	  //if these exist it will account for their values...not really sure that it's necessary
	  if (newMovie.format)
	    strcpy(t->info.format, newMovie.format);
	  if (newMovie.date)
	    strcpy(t->info.date, newMovie.date); 
        }
    }
  //tree was not null 
  else if(strcmp(newMovie.avlTitle, t->info.avlTitle) < 0 ) //newMovie is less than current node
    {
      t->left = insert( newMovie, t->left );  //recurse to left subtree
      if((height( t->left ) - height( t->right)) == 2 ) {
	//rotations to balance avl
	if( strcmp(newMovie.avlTitle, t->left->info.avlTitle) < 0 ) 
	  t = single_rotate_with_left( t );    
	else
                t = double_rotate_with_left( t );
      }
    }
  else if( strcmp(newMovie.avlTitle, t->info.avlTitle) > 0) //newMovie is greater than current node 
    {
      t->right = insert( newMovie, t->right ); //recurse to right subtree
      if( height( t->right ) - height( t->left ) == 2 ) {
	//rotations to balance avl 
	if( strcmp(newMovie.avlTitle, t->right->info.avlTitle) > 0 )
                t = single_rotate_with_right( t );
	else
	  t = double_rotate_with_right( t );
      }    
      
    }
  /* Else X is in the tree already; we'll do nothing */  
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    
    return t;
}

/*delete a node from the avl tree*/
node* del(node *tTree, char *delItem) /* delete( main body) */
{
  if(!(tTree))
        return tTree;
  
  if(strcmp(delItem, tTree->info.avlTitle) < 0) //delItem less than current title 
    tTree->left = del(tTree->left, delItem); //recurse left
    else 
      if(strcmp(delItem, tTree->info.avlTitle) > 0) //delItem greater than current title
	tTree->right = del(tTree->right, delItem); //recurse right
      else //equivalent
        {
	    node *oTree = tTree;
            if((tTree->left) && (tTree->right)) //two children
            {
	      node *parent = tTree->right;  //new parent is right subtree
	      tTree = parent->left; //gross successor stuff from here down
                if (tTree)
                {
                    while(tTree->left)
                    {
                        parent = tTree;
                        tTree = tTree->left;
                    }
                    parent->left = tTree->right;
                    tTree->right = oTree->right;
                }
                else
                    tTree = parent;
                tTree->left = oTree->left;
            }
            else
	      if(tTree->left) //only left child
                    tTree = tTree->left;
	      else //only right child
                    tTree = tTree->right;
            free(oTree);
        }
    
    return tTree;
}

/*get data of a node
char* get(node* n) {
    return n->info.Title;
}*/

/*Recursively display AVL tree or subtree*/
void display_avl(node* t) {
 
  if (t == NULL)
        return;
   
  printf(" %s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres); 
  
  display_avl(t->left);
  display_avl(t->right);
}

/*Recursively print all matches for the user's input and save them to an array*/
void display_matches(node* t, char *userInput, struct Movie *matches, int *count) { 
   
  printf("counter value is: %d\n", *count); 
  if (*count > 30) { 
    return;
  }
  
  int len;
  len = strlen(userInput);
  
  if (t == NULL)
    return;

  if (len == strlen(t->info.avlTitle) && strcmp(userInput, t->info.avlTitle) == 0) {
    printf("Exact match!\n");
  }

  if(strstr(t->info.avlTitle, userInput)) { 
    strcpy(matches[*count].Title, t->info.Title);
    strcpy(matches[*count].releaseYear,t->info.releaseYear);
    strcpy(matches[*count].runtimeMinutes,t->info.runtimeMinutes);
    strcpy(matches[*count].genres,t->info.genres);
    strcpy(matches[*count].avlTitle,t->info.avlTitle);
    printf("%s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres);
    (*count)++; 
  }
    
  display_matches(t->left, userInput, matches, count);
  display_matches(t->right, userInput, matches, count);   
}

/*Recursively display user's AVL tree*/
void display_user(node* t) {

  if (t == NULL)
        return;
  
  printf("%s\t%s\t%s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres,t->info.date, t->info.format);
  display_user(t->left);
  display_user(t->right);
}

/*Print to user's text file at end of */ 
void print_to_text(node*t, FILE *userFile) {
  if (t == NULL)
        return;
  
  fprintf(userFile, "%s\t%s\t%s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres,t->info.date, t->info.format);

  print_to_text(t->left, userFile);
  print_to_text(t->right, userFile);
}

/*display user's choice from retrieve*/
void display_userChoice(node* t, char *str) {
  if (t == NULL)
    return;
  int len = strlen(str); 
  if (strcmp(str, t->info.avlTitle) == 0 && len == strlen(t->info.avlTitle)); 
  printf("%s\t%s\t%s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres,t->info.date, t->info.format);
  display_userChoice(t->left, str);
  display_userChoice(t->right, str);
}

    

