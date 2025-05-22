#include "myStack.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char input[501];
    char input_go[500][10];  
    Stack* S = createEmptyStack();

    int num_count = 0;
    int oper_count = 0;

    printf("Enter the postfix Expression (must end with '#'): ");
    fgets(input, 501, stdin);  

    int h = strlen(input);

    // Ensure expression ends with '#'
    if (input[h - 2] != '#') {
        printf("Error: Expression must end with '#'.\n");
        free(S);
        return 1;
    }

    int j = 0, k = 0;

    // Parse input into tokens
    for (int g = 0; g < h - 1; g++) { 
        if (input[g] != ' ' && input[g] != ',' && input[g] != '\n' && input[g] != '\0') {
            input_go[j][k] = input[g];
            k++;
        } else {
            if (k != 0) {
                input_go[j][k] = '\0';  
                j++;
                k = 0;  
            }
        }
    }


    // Evaluate the postfix expression
    for (int i = 0; i < j; i++) {
        if (isdigit(input_go[i][0]) || ((input_go[i][0] == '-' || input_go[i][0] == '+') && isdigit(input_go[i][1]))) {
            double num = atof(input_go[i]);  
            push(S, num);
            num_count++;  
        } else if (input_go[i][0] == '+') {
            double a = pop(S);
            double b = pop(S);
            push(S, b + a);
            oper_count++;  
        } else if (input_go[i][0] == '-') {
            double a = pop(S);
            double b = pop(S);
            push(S, b - a);
            oper_count++;  
        } else if (input_go[i][0] == '*') {
            double a = pop(S);
            double b = pop(S);
            push(S, b * a);
            oper_count++;  
        } else if (input_go[i][0] == '/') {
            double a = pop(S);
            double b = pop(S);
            if (a != 0) {
                push(S, b / a);
            } else {
                printf("\nDivision by zero is Invalid\n");
                break;
            }
            oper_count++;  
        }
    }

    // Check validity of expression
    if (num_count != oper_count + 1) {
        printf("Invalid Expression.\n");
    } else {
        double result = pop(S);
        printf("Result: %.3f\n", result);
    }

    free(S);
    return 0;
}
