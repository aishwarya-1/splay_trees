#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include "header.h"

int main()
{
     tree *root;//the root element
     tree *x;//x is which element will come to root.
     int i;
     root = NULL;
     int choice = 0;
     int ele;
     while(1)
     {
         printf("\n\n 1.Insert");
         printf("\n\n 2.Delete");
         printf("\n\n 3.Search");
         printf("\n\n 4.Display\n");
         printf("\n\n Enter your choice:");
         scanf("%d",&choice);
         if(choice==5)
            exit(0);
         switch(choice)
         {
             case 1:
                printf("\n\n Enter the element to be inserted:");
                scanf("%d",&ele);
                x = insert(root,ele);
                if(root != NULL)
                {
                    splay(x,root);
                }
                root = x;
             break;

             case 2:
                 if(root == NULL)
                 {
                     printf("\n Empty tree...");
                     continue;
                 }
                 printf("\n\n Enter the element to be delete:");
                 scanf("%d",&ele);
                 root = delete(root, ele);
             break;

             case 3:
                 printf("Enter the element to be search\n");
                 scanf("%d",&ele);
                 x = lookup(root,ele);
                 splay(x,root);
                 if(x->data!=ele)
                 {
                     printf("Element not found\n");
                 }
                 root = x;
             break;

             case 4:
                 printf("The elements are\n");
                 print_ascii_tree(root);
             break;

             default:
             printf("Wrong choice\n");
             break;

         }
     }
}
