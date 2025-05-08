#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void generate_tac(char *expression) {
    int temp_count = 0;  // For naming temporary variables like t0, t1, ...
    char left_var[50];
    char operator[5];
    char right_var1[50];
    char right_var2[50];
    char* token = strtok(expression, " ");
    
    // Extract the left-hand side variable (e.g., 'a' in a = b + c * d)
    sscanf(token, "%s", left_var);
    token = strtok(NULL, " ");  // Skip the '=' sign
    token = strtok(NULL, " ");  // Get the first operand (b)
    
    // Start processing the right-hand side expression
    while (token != NULL) {
        if (isdigit(token[0]) || isalpha(token[0])) {  // Operand (could be variable or number)
            if (temp_count == 0) {
                strcpy(right_var1, token);
            } else if (temp_count == 1) {
                strcpy(right_var2, token);
            }
        } else if (strchr("+-*/", token[0]) != NULL) {  // Operator
            strcpy(operator, token);
            if (temp_count == 0) {
                // If no temp value exists, just initialize with the first operand
                temp_count++;
            } else {
                // Handle operator precedence and generate TAC
                if (strcmp(operator, "*") == 0) {
                    // Multiplication operation
                    printf("t%d = %s * %s\n", temp_count, right_var1, right_var2);
                    sprintf(left_var, "t%d", temp_count);  // Use temp result for next operation
                    temp_count++;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    
    // Handle the addition (or other operators after multiplication)
    printf("t%d = %s + %s\n", temp_count, left_var, right_var2);
    printf("%s = t%d\n", left_var, temp_count);
}

int main() {
    char expression[100];

    // Get the input expression
    printf("Enter the arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;  // Remove newline character if present

    // Generate the TAC
    printf("Generated TAC:\n");
    generate_tac(expression);

    return 0;
}
