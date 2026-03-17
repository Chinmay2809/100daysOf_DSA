#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;
    
    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];
        
        // If token is an operator (single character and not part of a negative number)
        if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || 
            token[0] == '*' || token[0] == '/')) {
            
            // Check if we have at least 2 operands
            if (top < 1) {
                // Invalid expression
                free(stack);
                return 0;
            }
            
            int b = stack[top--];
            int a = stack[top--];
            int result;
            
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: result = 0;
            }
            
            stack[++top] = result;
        } 
        else {
            // Token is a number
            stack[++top] = atoi(token);
        }
    }
    
    // Check if we have exactly one result
    int result = (top == 0) ? stack[top] : 0;
    free(stack);
    return result;
}