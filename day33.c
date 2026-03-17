#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int calculate(char* s) {
    int len = strlen(s);
    int* stack = (int*)malloc(len * sizeof(int));
    int top = -1;
    
    char lastOperator = '+';
    int currentNumber = 0;
    
    for (int i = 0; i <= len; i++) {
        char c = s[i];
        
        // If current character is a digit, build the number
        if (isdigit(c)) {
            currentNumber = currentNumber * 10 + (c - '0');
        }
        
        // If current character is an operator or we're at the end of string
        if (c == '+' || c == '-' || c == '*' || c == '/' || i == len) {
            // Process based on the last operator
            switch (lastOperator) {
                case '+':
                    stack[++top] = currentNumber;
                    break;
                case '-':
                    stack[++top] = -currentNumber;
                    break;
                case '*':
                    stack[top] = stack[top] * currentNumber;
                    break;
                case '/':
                    stack[top] = stack[top] / currentNumber;
                    break;
            }
            
            // Update last operator and reset current number
            lastOperator = c;
            currentNumber = 0;
        }
    }
    
    // Sum up all numbers in stack
    int result = 0;
    for (int i = 0; i <= top; i++) {
        result += stack[i];
    }
    
    free(stack);
    return result;
}