typedef struct tree
{
     int data;
     struct tree *parent;
     struct tree *left;
     struct tree *right;
}tree;

tree *rightrotation(tree *p,tree *root);
tree *leftrotation(tree *p,tree *root);
void splay (tree *x, tree *root);

tree *insert(tree *p,int value);
tree *delete(tree *p,int value);

tree *lookup(tree *p,int value);

void print_ascii_tree(tree *t);

