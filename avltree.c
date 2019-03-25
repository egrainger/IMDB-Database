/* Code courtesy of http://www.zentut.com/c-tutorial/c-avl-tree/ 
    https://www.techiedelight.com/find-inorder-successor-given-key-bst/
    https://stackoverflow.com/questions/10988677/deleting-an-element-in-avl-trees-in-c
    https://www.thecrazyprogrammer.com/2014/03/c-program-for-avl-tree-implementation.html
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
  
  if(strncmp(str, t->info.avlTitle, len) < 0)
    return find(str, t->left);

  else if(strncmp(str, t->info.avlTitle, len) > 0)
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
        {
	  strcpy(t->info.Title, newMovie.Title);    
	  strcpy(t->info.releaseYear ,newMovie.releaseYear);
	  strcpy(t->info.runtimeMinutes ,newMovie.runtimeMinutes);
	  strcpy(t->info.genres ,newMovie.genres);
	  strcpy(t->info.avlTitle ,newMovie.avlTitle);	 
	  t->height = 0;
	  t->left = t->right = NULL;
	  if (newMovie.format)
	    strcpy(t->info.format, newMovie.format);
	  if (newMovie.date)
	    strcpy(t->info.date, newMovie.date); 
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
    
    return t;
}

/*Find the successor node*/
node* successor(char *str, node *t, node* succ) {
  //base case
  if (t == NULL) {
    succ = NULL;
    return succ; 
  }

  //if node with key's value is found, the successor is min value node in its right subtree (if any)
  if (strcmp(str, t->info.avlTitle) == 0) {
    if (t->right)
      succ = find_min(t->right);
  }

  //if given key is less than the root node recurse for left subtree
  else if (strcmp(str, t->info.avlTitle) < 0) {
    //update successor to current node before recursing left subtree
    succ = t;
    successor(str, t->left, succ); 
  }
  //if given key is more than the root node, recurse for right subtree
  else
    successor(str, t->right, succ); 
}

int balance_factor(node *t)
{
	int lh,rh;
	if(t == NULL)
	  return(0);
	
	if(t->left == NULL)
	  lh = 0;
	else
	  lh = 1 + t->left->height;
	
	if(t->right == NULL)
	  rh = 0;
	else
	  rh = 1 + t->right->height;
	
	return(lh-rh);
}

/*remove a node in the tree*/
//FIXME
node* delete(node* t, char *str ) {
  struct node *remove_node;
  //If empty can't delete
  if (t == NULL){
    return t;
  }
  
  //Check to find stuff
  if (strcmp(str, t->info.avlTitle) < 0) {
    t->left = delete(t->left, str);
    
  } else if (strcmp(str, t->info.avlTitle) > 0) {
    t->right = delete(t->right,str);
  }
  else {

    if ((t->left == NULL) && (t->right != NULL)){
      remove_node = t->right;
      *t = *remove_node;
      dispose(remove_node); // this is for free-ing the memory
      
    } else if ((t->right == NULL)  && (t->left != NULL)){
      remove_node = t->left;
      *t = *remove_node;
      dispose(remove_node);
	    
    } else if ((t->right == NULL)  && (t->left == NULL)){
      remove_node = t;
      t = NULL;
      
    } else {
      node* succ = NULL; 
      remove_node = successor(str, t, succ);
      t->info.avlTitle = remove_node->info.avlTitle;
      t->right = delete(t->right, remove_node->info.avlTitle);
    }

    }

    if (t == NULL) {
        return t;

    if (balance_factor(t) == 2){
        if (balance_factor(t->left) == -1) {
	  return single_rotate_with_right(t); 

        } else if (balance_factor(t->left) == 1) {
	  return double_rotate_with_left(t); 
        }
    }

    if (balance_factor(t) == -2) {
        if (balance_factor(t->right) == -1) {
	  return single_rotate_with_left(t); 
	}

	else if (balance_factor(t->right) == 1)  { 
	  return double_rotate_with_right(t); 
            }
        }
    }

    return t;    
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
void display_matches(node* t, char *userInput, struct Movie *matches) { 
  static int counter = 1;
  printf("counter value is: %d\n", counter); 
  if (counter > 30) { 
    return;
  }

  int index;
  index = (counter-1) % 30;
  int len;
  len = strlen(userInput);
  
  if (t == NULL)
    return;

  if (len == strlen(t->info.avlTitle) && strcmp(userInput, t->info.avlTitle) == 0) {
    printf("Exact match!\n");
  }

  if(strstr(t->info.avlTitle, userInput)) {
    printf("%d\t", index);
    counter++;
    strcpy(matches[index].Title, t->info.Title);
    strcpy(matches[index].releaseYear,t->info.releaseYear);
    strcpy(matches[index].runtimeMinutes,t->info.runtimeMinutes);
    strcpy(matches[index].genres,t->info.genres);
    strcpy(matches[index].avlTitle,t->info.avlTitle);
    printf("%s\t%s\t%s\t%s\n",t->info.Title, t->info.releaseYear, t->info.runtimeMinutes, t->info.genres);
  }
    
  display_matches(t->left, userInput, matches);
  display_matches(t->right, userInput, matches);  
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
    

