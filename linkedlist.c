#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "buffer.h"
#include "newSleep.h"
#include "gameMap.h"
#include "carMove.h"
#include "linkedlist.h"

void freeStruct(void* data)
{
    free(data);
}

/*void freeCar (void* data)
{
    free(data);
}*/

/* function to create linked list */
LinkedList* createLinkedList()  
{
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->count = 0;
    return list;
}

/* function to create player node */
player* playerNode(player* pInfo)   
{
    player* pNode = (player*) malloc(sizeof(player));
    pNode->pCol = pInfo->pCol;
    pNode->pRow = pInfo->pRow;
    pNode->curCol = pInfo->curCol;
    pNode->curRow = pInfo->curRow;
    pNode->road = pInfo->road;
    return pNode;
}

/* function to create car node */
car* carNode(car* cInfo)    
{
    car* cNode = (car*) malloc(sizeof(car));
    cNode->column = cInfo->column;
    cNode->row = cInfo->row;
    cNode->direction = cInfo->direction;
    return cNode;
}

/* function to insert value to the last node of linked list */
void insertLast(LinkedList* list, void* entry) 
{
    LinkedListNode* newNode = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    LinkedListNode* currentNode = list->head;
    newNode->data = entry;
    newNode->next = NULL;

    if(list->head == NULL) /* condition for when the linked list is empty */
    {
        list->head = newNode;
    }
    else
    {
        while(currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
    list->count++;  
}

/* function to remove the last node from the linked list */
void* removeLast(LinkedList* list)
{
    LinkedListNode* node = list->head;
    void* prev = list->head->data;
    if(list->head == NULL)
    {
        return 0;
    }
    else if(node->next == NULL)
    {
        list->head = node->next;
    }
    else
    {
        while(node->next->next != NULL)
        {
            node = node->next;
        }
        prev = node->next->data;
        node->next = NULL;
    }
    list->count--;
    return prev;
}

void freeLinkedList (LinkedList* list, listFunc funcPtr)
{
    LinkedListNode* current = list->head;
    LinkedListNode* node;
    while(current != NULL)
    {
        node = current;
        current = current->next;
        funcPtr(node->data);
        free(node);
    }
    free(list);
}