#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* Basic structure for a node in a circular linked list*/

typedef struct node
{
    int value;
    struct node* prev;
    struct node* next;
} node;

/* Creates a single node having data value, and returns a pointer to it */
node* createListNode(int value);

/* Node x is a node assumed to be in some circular list.
Inserts node y after node x. Returns pointer to inserted element position.
If x is NULL, code should still create the list with a single node y and return it. */
node* insertNode(node* x, node* y);

/* Deletes node x. Returns pointer to next element in the list, NULL if none are remaining */
node* deleteNode(node* x);

/* Merges two lists specified by pointers x,y. Order does not matter */
node* mergeList(node* x, node* y);

/* Prints the list */
void printList(node* x);

/* Checks if the list is empty */
bool isEmpty(node* x);

