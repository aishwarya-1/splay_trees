#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include "header.h"
#include "header_k.h"

int main()
{
     tree *root;//the root element
     tree *x;//x is which element will come to root.
     int i;
     root = NULL;
     int choice = 0;
     int ele;

     RecentNodes List;

     int k;
     printf("Enter the number of recent nodes: ");
     scanf("%d",&k);
     initialize(&List, k);

     while(1)
     {
         printf("\n\n 1.Insert");
         printf("\n\n 2.Delete");
         printf("\n\n 3.Search");
         printf("\n\n 4.Display\n");
         printf("\n\n 5.Print %d recent nodes\n", k);
         printf("\n\n Enter your choice:");
         scanf("%d",&choice);

         switch(choice)
         {
             case 1:
                printf("\n\n Enter the element to be inserted:");
                scanf("%d", &ele);
                isKeyRecent(&List, ele);
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
                 printf("\n\n Enter the element to be deleted:");
                 scanf("%d",&ele);
                 x = lookup(root,ele);
                 if(x->data!=ele)
                 {
                     isKeyRecent(&List, root->data);
                     continue;
                 }
                 delete_ll(&List, ele);
                 root = delete(root, ele);
                 if(root->data!=NULL)
                 {
                     isKeyRecent(&List, root->data);
                 }
             break;

             case 3:
                 printf("Enter the element to be searched\n");
                 scanf("%d",&ele);
                 x = lookup(root,ele);
                 splay(x,root);
                 if(x->data!=ele)
                 {
                     printf("Element not found\n");
                 }
                 root = x;
                 isKeyRecent(&List, root->data);
             break;

             case 4:
                 printf("The elements are\n");
                 print_ascii_tree(root);
             break;

             case 5:
                printRecent(List);
             break;

             case 6:
                exit(0);
             break;

             default:
             printf("Wrong choice\n");
             break;
         }
     }
}
