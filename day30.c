#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
    int n = strlen(s);
    char stack[n];
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        char current = s[i];
        
        // If it's an opening bracket, push to stack
        if (current == '(' || current == '[' || current == '{') {
            stack[++top] = current;
        }
        // If it's a closing bracket
        else {
            // If stack is empty, no matching opening bracket
            if (top == -1) {
                return false;
            }
            
            char topChar = stack[top];
            
            // Check if the closing bracket matches the top opening bracket
            if ((current == ')' && topChar != '(') ||
                (current == ']' && topChar != '[') ||
                (current == '}' && topChar != '{')) {
                return false;
            }
            
            // Valid match, pop from stack
            top--;
        }
    }
    
    // Valid if stack is empty (all brackets closed)
    return top == -1;
}