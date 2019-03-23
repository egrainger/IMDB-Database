/* Code courtesy of http://www.zentut.com/c-tutorial/c-avl-tree/ */
//Code updated to work with my needs
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
//struct Movie find(char *str, node* t ) {
node *find(char *str, node*t){ 
  int len;
  len = strlen(str); 

  //struct Movie movie = {0}; 
  node* n = {0}; 
  
  if( t == NULL )
    return n;
  
  if(strncmp(str, t->info.avlTitle, len) < 0)
    return find(str, t->left);

  else if(strncmp(str, t->info.avlTitle, len) > 0)
    return find(str, t->right);

  else
    //return t->info;
    return n; 
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
        {
	  strcpy(t->info.Title, newMovie.Title);    
	  strcpy(t->info.releaseYear ,newMovie.releaseYear);
	  strcpy(t->info.runtimeMinutes ,newMovie.runtimeMinutes);
	  strcpy(t->info.genres ,newMovie.genres);
	  strcpy(t->info.avlTitle ,newMovie.avlTitle);	 
	  t->height = 0;
	  t->left = t->right = NULL;
        }
    }
  else if(strcmp(newMovie.avlTitle, t->info.avlTitle) < 0 )
    {
      t->left = insert( newMovie, t->left );
      if((height( t->left ) - height( t->right)) == 2 ) {
	if( strcmp(newMovie.avlTitle, t->left->info.avlTitle) < 0 )
	  t = single_rotate_with_left( t );    
	else
                t = double_rotate_with_left( t );
      }
    }
  else if( strcmp(newMovie.avlTitle, t->info.avlTitle) > 0)
    {
      t->right = insert( newMovie, t->right );
      if( height( t->right ) - height( t->left ) == 2 ) {
	if( strcmp(newMovie.avlTitle, t->right->info.avlTitle) > 0 )
                t = single_rotate_with_right( t );
	else
	  t = double_rotate_with_right( t );
      }    
      
    }
  /* Else X is in the tree already; we'll do nothing */
  
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    //printf("%s\n", t->info.Title);
    return t;
}

/*remove a node in the tree*/
//FIXME
node* delete( char* str, node* t ) {
    printf( "Sorry; Delete is unimplemented; %s remains\n", str );
    return t;
}

/*get data of a node*/
//FIXME
char* get(node* n) {
    return n->info.Title;
}

/*Recursively display AVL tree or subtree*/
//FIXME
void display_avl(node* t) {
  //printf("DISPLAY!\n"); 
  if (t == NULL)
        return;
  //printf("got past empty"); 
  printf(" %s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres);
  
  /*if(t->left != NULL)
    printf("(L:\t%s\t%s\t%s\t%s\t",t->info.Title, t->info.releaseYear,t->info.runtimeMinutes,t->info.genres);
  if(t->right != NULL)
        printf("(R:\t%s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear,t->info.runtimeMinutes,t->info.genres);
  printf("\n");
  */
  display_avl(t->left);
  display_avl(t->right);
}
