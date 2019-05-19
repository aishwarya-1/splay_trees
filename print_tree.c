#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

tree* make_empty(tree *t)
{
  if (t != NULL)
  {
    make_empty(t->left);
    make_empty(t->right);
    free(t);
  }

  return NULL;
}

tree* find_min(tree *t)
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (t->left == NULL)
  {
    return t;
  }
  else
  {
    return find_min(t->left);
  }
}

tree* find_max(tree *t)
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (t->right == NULL)
  {
    return t;
  }
  else
  {
    return find_max(t->right);
  }
}

tree* find(int elem, tree *t)
{
  if (t == NULL)
  {
    return NULL;
  }

  if (elem < t->data)
  {
    return find(elem, t->left);
  }
  else if (elem > t->data)
  {
    return find(elem, t->right);
  }
  else
  {
    return t;
  }
}

//Insert i into the tree t, duplicate will be discarded
//Return a pointer to the resulting tree.
tree* insert_p(int value, tree *t)
{
  tree * new_tree;

  if (t == NULL)
  {
    new_tree = (tree *) malloc (sizeof (tree));
    if (new_tree == NULL)
    {
	    return t;
    }

    new_tree->data = value;

	  new_tree->left = new_tree->right = NULL;
	  return new_tree;
  }

  if (value < t->data)
  {
    t->left = insert_p(value, t->left);
  }
  else if (value > t->data)
  {
	  t->right = insert_p(value, t->right);
  }
  else
  {
    //duplicate, ignore it
	  return t;
  }
  return t;
}

tree* delete_p(int value, tree * t)
{
  //Deletes tree from the tree
  // Return a pointer to the resulting tree
  tree * x;
  tree *tmp_cell;

  if (t==NULL) return NULL;

  if (value < t->data)
  {
    t->left = delete_p(value, t->left);
  }
  else if (value > t->data)
  {
	  t->right = delete_p(value, t->right);
  }
  else if (t->left && t->right)
  {
    tmp_cell = find_min(t->right);
    t->data = tmp_cell->data;
    t->right = delete_p(t->data, t->right);
  }
  else
  {
    tmp_cell = t;
    if (t->left == NULL)
      t = t->right;
    else if (t->right == NULL)
      t = t->left;
    free(tmp_cell);
  }

  return t;
}

//printing tree in ascii

typedef struct asciitree_struct asciitree;

struct asciitree_struct
{
  asciitree * left, * right;

  //length of the edge from this tree to its children
  int edge_length;

  int height;

  int lablen;

  //-1=I am left, 0=I am root, 1=right
  int parent_dir;

  //max supported unit32 in dec, 10 digits max
  char label[11];
};


#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between left and right trees
int gap = 3;

//used for printing next tree in the same level,
//this is the x coordinate of the next char printed
int print_next;

int MIN (int X, int Y)
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}

asciitree * build_ascii_tree_recursive(tree * t)
{
  asciitree * tree;

  if (t == NULL) return NULL;

  tree = malloc(sizeof(asciitree));
  tree->left = build_ascii_tree_recursive(t->left);
  tree->right = build_ascii_tree_recursive(t->right);

  if (tree->left != NULL)
  {
    tree->left->parent_dir = -1;
  }

  if (tree->right != NULL)
  {
    tree->right->parent_dir = 1;
  }

  sprintf(tree->label, "%d", t->data);
  tree->lablen = strlen(tree->label);

  return tree;
}


//Copy the tree into the ascii tree structre
asciitree * build_ascii_tree(tree * t)
{
  asciitree *tree;
  if (t == NULL) return NULL;
  tree = build_ascii_tree_recursive(t);
  tree->parent_dir = 0;
  return tree;
}

//Free all the trees of the given tree
void free_ascii_tree(asciitree *tree)
{
  if (tree == NULL) return;
  free_ascii_tree(tree->left);
  free_ascii_tree(tree->right);
  free(tree);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciitree *tree, int x, int y)
{
  int i, isleft;
  if (tree == NULL) return;
  isleft = (tree->parent_dir == -1);
  lprofile[y] = MIN(lprofile[y], x-((tree->lablen-isleft)/2));
  if (tree->left != NULL)
  {
	  for (i=1; i <= tree->edge_length && y+i < MAX_HEIGHT; i++)
    {
	    lprofile[y+i] = MIN(lprofile[y+i], x-i);
    }
  }
  compute_lprofile(tree->left, x-tree->edge_length-1, y+tree->edge_length+1);
  compute_lprofile(tree->right, x+tree->edge_length+1, y+tree->edge_length+1);
}

void compute_rprofile(asciitree *tree, int x, int y)
{
  int i, notleft;
  if (tree == NULL) return;
  notleft = (tree->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((tree->lablen-notleft)/2));
  if (tree->right != NULL)
  {
	  for (i=1; i <= tree->edge_length && y+i < MAX_HEIGHT; i++)
    {
	    rprofile[y+i] = MAX(rprofile[y+i], x+i);
    }
  }
  compute_rprofile(tree->left, x-tree->edge_length-1, y+tree->edge_length+1);
  compute_rprofile(tree->right, x+tree->edge_length+1, y+tree->edge_length+1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciitree *tree)
{
  int h, hmin, i, delta;
  if (tree == NULL) return;
  compute_edge_lengths(tree->left);
  compute_edge_lengths(tree->right);

  /* first fill in the edge_length of tree */
  if (tree->right == NULL && tree->left == NULL)
  {
	  tree->edge_length = 0;
  }
  else
  {
    if (tree->left != NULL)
    {
	    for (i=0; i<tree->left->height && i < MAX_HEIGHT; i++)
      {
		    rprofile[i] = -INFINITY;
	    }
	    compute_rprofile(tree->left, 0, 0);
	    hmin = tree->left->height;
    }
    else
    {
	    hmin = 0;
    }
	  if (tree->right != NULL)
    {
	    for (i=0; i<tree->right->height && i < MAX_HEIGHT; i++)
      {
		    lprofile[i] = INFINITY;
	    }
	    compute_lprofile(tree->right, 0, 0);
	    hmin = MIN(tree->right->height, hmin);
    }
    else
    {
	    hmin = 0;
    }
	  delta = 4;
	  for (i=0; i<hmin; i++)
    {
	    delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
    }

    //If the tree has two children of height 1, then we allow the
    //two leaves to be within 1, instead of 2
	  if (((tree->left != NULL && tree->left->height == 1) ||
	      (tree->right != NULL && tree->right->height == 1))&&delta>4)
    {
      delta--;
    }

    tree->edge_length = ((delta+1)/2) - 1;
  }

  //now fill in the height of tree
  h = 1;
  if (tree->left != NULL)
  {
	  h = MAX(tree->left->height + tree->edge_length + 1, h);
  }
  if (tree->right != NULL)
  {
	  h = MAX(tree->right->height + tree->edge_length + 1, h);
  }
  tree->height = h;
}

//This function prints the given level of the given tree, assuming
//that the tree has the given x cordinate.
void print_level(asciitree *tree, int x, int level)
{
  int i, isleft;
  if (tree == NULL) return;
  isleft = (tree->parent_dir == -1);
  if (level == 0)
  {
	  for (i=0; i<(x-print_next-((tree->lablen-isleft)/2)); i++)
    {
	    printf(" ");
    }
	  print_next += i;
	  printf("%s", tree->label);
	  print_next += tree->lablen;
  }
  else if (tree->edge_length >= level)
  {
	  if (tree->left != NULL)
    {
	    for (i=0; i<(x-print_next-(level)); i++)
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("/");
	    print_next++;
    }
	  if (tree->right != NULL)
    {
	    for (i=0; i<(x-print_next+(level)); i++)
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("\\");
	    print_next++;
    }
  }
  else
  {
	  print_level(tree->left,
                x-tree->edge_length-1,
                level-tree->edge_length-1);
	  print_level(tree->right,
                x+tree->edge_length+1,
                level-tree->edge_length-1);
  }
}

//prints ascii tree for given tree structure
void print_ascii_tree(tree *t)
{
  asciitree *proot;
  int xmin, i;
  if (t == NULL) return;
  proot = build_ascii_tree(t);
  compute_edge_lengths(proot);
  for (i=0; i<proot->height && i < MAX_HEIGHT; i++)
  {
	  lprofile[i] = INFINITY;
  }
  compute_lprofile(proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
  {
	  xmin = MIN(xmin, lprofile[i]);
  }
  for (i = 0; i < proot->height; i++)
  {
	  print_next = 0;
	  print_level(proot, -xmin, i);
	  printf("\n");
  }
  if (proot->height >= MAX_HEIGHT)
  {
	  printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
  }
  free_ascii_tree(proot);
}

//driver routine
/*void main()
{
  //A sample use of these functions.  Start with the empty tree
  //insert some stuff into it, and then delete it
  tree *root;
  int i;
  root = NULL;

  make_empty(root);

  printf("\nAfter inserting data 10..\n");
  root = insert_p(10, root);
  print_ascii_tree(root);

  printf("\nAfter inserting data 5..\n");
  root = insert_p(5, root);
  print_ascii_tree(root);

  printf("\nAfter inserting data 15..\n");
  root = insert_p(15, root);
  print_ascii_tree(root);

  printf("\nAfter inserting datas 9, 13..\n");
  root = insert_p(9, root);
  root = insert_p(13, root);
  print_ascii_tree(root);

  printf("\nAfter inserting datas 2, 6, 12, 14, ..\n");
  root = insert_p(2, root);
  root = insert_p(6, root);
  root = insert_p(12, root);
  root = insert_p(14, root);
  print_ascii_tree(root);


  printf("\n\nAfter deleting a tree (14) with no child..\n");
  root = delete_p(14, root);
  print_ascii_tree(root);

  printf("\n\nAfter deleting a tree (13) with left child..\n");
  root = delete_p(13, root);
  print_ascii_tree(root);

  printf("\n\nAfter deleting a tree (5) with left and right children..\n");
  root = delete_p(5, root);
  print_ascii_tree(root);

    printf("\n\nAfter deleting a tree (10, root tree) with left and right children..\n");
  root = delete_p(10, root);
  print_ascii_tree(root);

  make_empty(root);
}
*/
