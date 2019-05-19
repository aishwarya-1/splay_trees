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
     if (x->right!=NULL) x->right->parent = p;
     x->right = p;
     if (p->parent!=NULL)
        if(p==p->parent->right) p->parent->right=x;
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
    if (x->left!=NULL) x->left->parent = p;
    x->left = p;
    if (p->parent!=NULL)
    if (p==p->parent->left) p->parent->left=x;
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
            par = temp1;//temp1 having the parent address,so that's it
            temp1->left = newNode;
            newNode->parent = temp1;//store the parent address.
        }
        else
        {
            par = temp1;//temp1 having the parent tree address.
            temp1->right = newNode;
            newNode->parent = par;//store the parent address
        }
    }
    return (newNode);
}

/*tree *inorder(tree *p)
{
     if(p != NULL)
     {
     inorder(p->left);
     printf("CURRENT %d\t",p->data);
     printf("LEFT %d\t",data_print(p->left));
     printf("PARENT %d\t",data_print(p->parent));
     printf("RIGHT %d\t\n",data_print(p->right));
     inorder(p->right);
     }
}*/


tree *delete(tree *p,int value)
{
     tree *x,*y,*p1;
     tree *root;
     tree *s;
     root = p;
     x = lookup(p,value);
     if(x->data == value)
     { //if the deleted element is leaf
         if((x->left == NULL) && (x->right == NULL))
         {
             y = x->parent;
             if(x ==(x->parent->right))
                y->right = NULL;
             else
                y->left = NULL;
             free(x);
         }
         //if deleted element having left child only
         else if((x->left != NULL) &&(x->right == NULL))
         {
             if(x == (x->parent->left))
             {
                 y = x->parent;
                 x->left->parent = y;
                 y->left = x->left;
                 free(x);
             }
             else
             {
                 y = x->parent;
                 x->left->parent = y;
                 y->right = x->left;
                 free(x);
             }
         }
        //if deleted element having right child only
        else if((x->left == NULL) && (x->right != NULL))
        {
            if(x == (x->parent->left))
            {
                y = x->parent;
                x->right->parent = y;
                y->left = x->right;
                free(x);
            }
            else
            {
                y = x->parent;
                x->right->parent = y;
                y->right = x->right;
                free(x);
            }
        }
    //if the deleted element having two child
    else if((x->left != NULL) && (x->right != NULL))
    {
        if(x == (x->parent->left))
        {
            s = sucessor(x);
            if(s != x->right)
            {
                y = s->parent;
                if(s->right != NULL)
                {
                    s->right->parent = y;
                    y->left = s->right;
                }
                else y->left = NULL;
                s->parent = x->parent;
                x->right->parent = s;
                x->left->parent = s;
                s->right = x->right;
                s->left = x->left;
                x->parent->left = s;
            }
            else
            {
                y = s;
                s->parent = x->parent;
                x->left->parent = s;
                s->left = x->left;
                x->parent->left = s;
             }
             free(x);
        }
             else if(x == (x->parent->right))
             {
             s = sucessor(x);
             if(s != x->right)
             {
             y = s->parent;
             if(s->right != NULL)
             {
             s->right->parent = y;
             y->left = s->right;
             }
             else y->left = NULL;
             s->parent = x->parent;
             x->right->parent = s;
             x->left->parent = s;
             s->right = x->right;
             s->left = x->left;
             x->parent->right = s;
             }
             else
             {
             y = s;
             s->parent = x->parent;
             x->left->parent = s;
             s->left = x->left;
             x->parent->right = s;
             }
             free(x);
         }
     }
     splay(y,root);
     }
     else
     {
     splay(x,root);
     }
}

tree *sucessor(tree *x)
{
    tree *temp,*temp2;
    temp=temp2=x->right;
    while(temp != NULL)
    {
        temp2 = temp;
        temp = temp->left;
    }
    return temp2;
}
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
tree *search(tree *p,int value)
{
    tree *x,*root;
    root = p;
    x = lookup(p,value);
    if(x->data == value)
    {
        printf("Inside search if\n");
        splay(x,root);
    }
    else
    {
        printf("Inside search else\n");
        splay(x,root);
    }
}
