#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_STACK_SIZE 500

typedef struct Stack
{
    double value[MAX_STACK_SIZE];
    unsigned top_index;
}Stack;

/* Functions for Stack operations */

Stack* createEmptyStack();
bool push(Stack *S,double number);
double pop(Stack *S);
double top(Stack S);
