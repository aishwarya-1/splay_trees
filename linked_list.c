#include<stdio.h>
#include<stdlib.h>
#include "header_k.h"

//Initializes the RecentNodes List at the beginning of the program
void initialize(RecentNodes *List, int k)
{
    List->head = NULL;
    List->tail = NULL;
    List->nodes = 0;
    List->maxNodes = k;
}

//Creates and Returns a New Node with key as its value and count of 1
Node *createNode(int key)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->value = key;
    temp->count = 1;
    temp->next = NULL;
    return temp;
}

//Inserts a New Node into the list
void insertNode(RecentNodes *List, int key)
{
    Node *newNode = createNode(key);
    newNode->next = List->head;
    List->head = newNode;
    if(List->nodes == 0)
        List->tail = newNode;
    List->nodes++;
}


//To check if the key is already present in the list or not
//IF present moves the node to front ELSE inserts a New Node at the front
void isKeyRecent(RecentNodes *List, int key)
{
    if(List->head == NULL){
        insertNode(List,key);
        return;
    }

    Node *temp = List->head;
    Node *ptr = temp;
    while(temp->value!=key && temp->next!=NULL){
        ptr = temp;
        temp = temp->next;
    }

    if(temp->next == NULL && temp->value!=key)
    {
        if(List->nodes == List->maxNodes)
        {
            Node *deleted = List->tail;
            ptr->next = NULL;
            free(deleted);
            List->tail = ptr;
            List->nodes--;
        }
        insertNode(List,key);
        return;
    }
    //returns 0 to indicate key not found in the list but has been inserted now

    if(List->tail == temp)
        List->tail = ptr;
    ptr->next = temp->next;
    if(temp!=List->head)
        temp->next = List->head;
    List->head = temp;
    temp->count++;
    
    return;
    //returns 1 to indicate key found in the list and has been moved to the front
}


//Prints the list containing k recent nodes
void printRecent(RecentNodes List)
{
    if(List.head == NULL){
        printf("List is currently empty!\n");
        return ;
    }
    Node *temp = List.head;
    printf("\nKeys:  ");
    while(temp!=NULL){
        printf("%6d ",temp->value);
        temp = temp->next;
    }
    temp = List.head;
    printf("\n\nCount: ");
    while(temp!=NULL){
        printf(" %5d ",temp->count);
        temp = temp->next;
    }
    printf("\n");
}

void delete_ll(RecentNodes *List, int ele)
{
    isKeyRecent(List, ele);
    if(List->nodes==1 && List->head->value==ele)
    {
        List->head = NULL;
        List->tail = NULL;
        List->nodes--;
        return;
    }
    Node *temp = List->head;
    List->head = temp->next;
    List->nodes--;
    temp->next = NULL;
    free(temp);
}
