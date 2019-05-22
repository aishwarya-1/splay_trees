#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include "header.h"

void splay (tree *x, tree *root)
{
    tree *p,*g;
    /*check if tree x is the root tree*/
    if(x==root)
        return;
    /*Performs Zig step*/
    else if(x->parent==root)
    {
        if(x==x->parent->left)
        root=rightrotation(root,root);
        else
        root=leftrotation(root,root);
    }
    else
    {
        p=x->parent; /*now points to parent of x*/
        g=p->parent; /*now points to parent of x's parent*/

        /*Performs the Zig-zig step when x is left and x's parent
        is left*/
        if(x==p->left&&p==g->left)
        {
            root=rightrotation(g,root);
            root=rightrotation(p,root);
        }

        /*Performs the Zig-zig step when x is right and x's parent
        is right*/
        else if(x==p->right&&p==g->right)
        {
            root=leftrotation(g,root);
            root=leftrotation(p,root);
        }
        /*Performs the Zig-zag step when x's is right and x's
        parent is left*/
        else if(x==p->right&&p==g->left)
        {
            root=leftrotation(p,root);
            root=rightrotation(g,root);
        }
        /*Performs the Zig-zag step when x's is left and x's parent
        is right*/
        else if(x==p->left&&p==g->right)
        {
            root=rightrotation(p,root);
            root=leftrotation(g,root);
        }
        splay(x, root);
     }
}

tree *rightrotation(tree *p,tree *root)
{
     tree *x;
     x = p->left;
     p->left = x->right;
     if (x->right!=NULL)
        x->right->parent = p;
     x->right = p;
     if (p->parent!=NULL)
        if(p==p->parent->right)
            p->parent->right=x;
        else
            p->parent->left=x;
     x->parent = p->parent;
     p->parent = x;
     if (p==root)
        return x;
     else
        return root;
}
tree *leftrotation(tree *p,tree *root)
{
    tree *x;
    x = p->right;
    p->right = x->left;
    if (x->left!=NULL)
        x->left->parent = p;
    x->left = p;
    if (p->parent!=NULL)
        if (p==p->parent->left)
            p->parent->left=x;
    else
        p->parent->right=x;
    x->parent = p->parent;
    p->parent = x;
    if(p==root)
        return x;
    else
        return root;
}

tree *create_node(int value)
{
    tree *n = (tree *)malloc(sizeof(tree));
    n->data = value;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}

tree *insert(tree *p, int value)
{
    tree *newNode = create_node(value);
    tree *temp1,*temp2,*par;
    if(p == NULL)
    {
        p =  newNode;
        return(p);
    }
    else
    {
        temp2 = p;
        while(temp2 != NULL)
        {
            temp1 = temp2;
            if(temp2->data > value)
                temp2 = temp2->left;
            else if(temp2->data < value)
                temp2 = temp2->right;
            else if(temp2->data == value)
                return temp2;
        }
        if(temp1->data > value)
        {
            temp1->left = newNode;
        }
        else
        {
            temp1->right = newNode;
        }
        newNode->parent = temp1;//store the parent address
    }
    return (newNode);
}

// The delete function for Splay tree. Note that this function
// returns the new root of Splay Tree after removing the key
tree* delete(tree *root, int key)
{
    tree *temp;
    if (!root)
        return NULL;

    temp = root;
    tree *x = lookup(root, key);
    // Splay the given key
    splay(x, root);
    root = x;
    if(root->data!=key)
    {
        root = x;
        return root;
    }
    //print_ascii_tree(root);

    // If key is present
    // If left child of root does not exist
    // make root->right as root

    if (!root->left)
    {
        if(root->right!=NULL)
        {
            temp = root;
            //printf("%d\n", root->data);
            root = root->right;
            root->parent = NULL;
        }
        else
        {
            root = NULL;
            return root;
        }
    }

    // Else if left child exists
    else
    {
        //printf("%d\n", root->data);
        //print_ascii_tree(root);
        temp = root;
        tree *q = root->left;
        tree *q1;
        while(q!=NULL)
        {
            q1 = q;
            q = q->right;
        }
        //printf("%d\n", q1->data);
        splay(q1, root->left);
        //print_ascii_tree(root);
        root = q1;


        // Make right child of previous root  as
        // new root's right child
        if(temp->right!=NULL)
        {
            root->right = temp->right;
            temp->right->parent = root;
        }
        else
        {
            root->right = NULL;
        }

    }

    // free the previous root node, that is,
    // the node containing the key
    free(temp);

    // return root of the new Splay Tree
    return root;

}

//p is a root element of the tree
//p is a root element of the tree
tree *lookup(tree *p, int value)
{
    tree *temp1,*temp2;
    if(p != NULL)
    {
        temp1 = p;
        while(temp1 != NULL)
        {
            temp2 = temp1;
            if(temp1->data > value)
                temp1 = temp1->left;
            else if(temp1->data < value)
                temp1 = temp1->right;
            else
                return temp1;
        }
        return temp2;
    }
    else
    {
        printf("NO element in the tree\n");
        exit(0);
    }
}
