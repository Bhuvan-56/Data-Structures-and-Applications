#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 500

typedef struct Stack {
    double value[MAX_STACK_SIZE];
    int top_index;  
} Stack;

Stack* createEmptyStack();
void push(Stack *S, double number);
double pop(Stack *S);
double top(Stack *S);
int isStackEmpty(Stack *S);
int isStackFull(Stack *S);


