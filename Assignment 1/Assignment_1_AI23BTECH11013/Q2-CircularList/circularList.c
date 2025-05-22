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

/* Creates a new list node with the given value and returns a pointer to it */
node* createListNode(int value) {
    node* new_node = (node*)malloc(sizeof(node)); // Allocate memory for new node
    if (new_node == NULL) {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }

    // Initialize the new node to point to itself (circular)
    new_node->value = value;
    new_node->next = new_node;
    new_node->prev = new_node;
    return new_node;
}

/* Inserts node y after node x and returns a pointer to node y */
node* insertNode(node* x, node* y) {
    if (y == NULL) { // If node y is NULL, just return x
        return x;
    }

    if (x == NULL) {  // If node x is NULL, treat y as the only node
        y->next = y;
        y->prev = y;
        return y;  
    }

    // Insert y after x
    y->next = x->next;
    y->prev = x;
    x->next->prev = y;
    x->next = y;

    return y;
}

/* Deletes node x and returns the next node in the list */
node* deleteNode(node* x) {
    if (x == NULL) {
        printf("\nInvalid node\n");
        return NULL;
    }

    if (x->next == x && x->prev == x) { // If x is the only node in the list
        
        return NULL;  
    }

    node* nextNode = x->next;

    // Adjust the links to remove x from the list
    x->prev->next = x->next;
    x->next->prev = x->prev;

     

    return nextNode; // Return the next node
}

/* Prints all the nodes in the circular linked list starting from node x */
void printList(node* x) {
    if (x == NULL) {
        printf("\nList is empty\n");
        return;
    }

    node* temp = x; // Start from node x
    do {
        printf("%d ", temp->value);
        temp = temp->next; // Move to the next node
    } while (temp != x);

    printf("\n");
}

/* Checks if the circular linked list is empty */
bool isEmpty(node* x) {
    return (x == NULL);
}

/* Merges two circular linked lists, x and y, and returns the head of the merged list */
node* mergeList(node* x, node* y) {
    if (x == NULL || y == NULL) {
        printf("Error: One or both lists are NULL.\n");
        return NULL;
    }

    // Get the last nodes of both lists
    node* x_last = x->prev;
    node* y_last = y->prev;

    // Link the two lists together
    x_last->next = y;
    y->prev = x_last;

    y_last->next = x;
    x->prev = y_last;

    return x;
}