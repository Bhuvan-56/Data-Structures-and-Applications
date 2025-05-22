#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 500


typedef struct Stack {
    double value[MAX_STACK_SIZE];
    int top_index;  
} Stack;

Stack* createEmptyStack() {
    Stack* S = (Stack*) malloc(sizeof(Stack));
    if (S == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the stack.\n");
        exit(EXIT_FAILURE);  
    }
    S->top_index = -1;  
    return S;
}

int isStackFull(Stack *S) {
    return S->top_index >= MAX_STACK_SIZE - 1;
}

void push(Stack *S, double number) {
    if (isStackFull(S)) {
        fprintf(stderr, "Error: Stack overflow. Cannot push %0.3f onto the stack.\n", number);
        exit(EXIT_FAILURE);  
    }
    S->value[++S->top_index] = number;
    //printf("Pushed %0.3f onto the stack\n", number);
}

int isStackEmpty(Stack *S) {
    return S->top_index < 0;
}

double pop(Stack *S) {
    if (isStackEmpty(S)) {
        fprintf(stderr, "Error: Stack underflow. Less no of elements or No elements to pop.\n");
        exit(EXIT_FAILURE);  
    }
    double popped = S->value[S->top_index--];
    //printf("Popped %0.3f from the stack\n", popped);
    return popped;
}

double top(Stack *S) {
    if (isStackEmpty(S)) {
        fprintf(stderr, "Error: Stack is empty. No top element.\n");
        exit(EXIT_FAILURE);  
    }
    return S->value[S->top_index];
}

