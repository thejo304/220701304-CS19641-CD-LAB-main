#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to hold a TAC entry
typedef struct {
    char result[20];
    char operator[5];
    char operand1[20];
    char operand2[20];
} TAC;

// Function to trim the newline from a string
void trim_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Function to check if a TAC is a dead code (i.e., if the result is not used later)
bool is_dead_code(TAC tac, TAC *tac_list, int tac_count) {
    for (int i = 0; i < tac_count; i++) {
        if (strcmp(tac_list[i].operand1, tac.result) == 0 || strcmp(tac_list[i].operand2, tac.result) == 0) {
            return false; // Result is used somewhere later
        }
    }
    return true; // Result is not used later
}

// Function to check if an expression is a common sub-expression
bool is_common_subexpression(TAC tac, TAC *tac_list, int tac_count) {
    for (int i = 0; i < tac_count; i++) {
        // Check if the current expression already exists in previous ones
        if (strcmp(tac.operator, tac_list[i].operator) == 0 &&
            strcmp(tac.operand1, tac_list[i].operand1) == 0 &&
            strcmp(tac.operand2, tac_list[i].operand2) == 0) {
            return true; // Common sub-expression found
        }
    }
    return false;
}

// Function to remove a TAC entry (for dead code elimination)
void remove_dead_code(TAC *tac_list, int *tac_count, int index) {
    for (int i = index; i < *tac_count - 1; i++) {
        tac_list[i] = tac_list[i + 1];
    }
    (*tac_count)--; // Decrease the count of TAC
}

// Function to optimize the TAC with Dead Code Elimination (DCE) and Common Subexpression Elimination (CSE)
void optimize_tac(TAC *tac_list, int *tac_count) {
    for (int i = 0; i < *tac_count; i++) {
        if (is_dead_code(tac_list[i], tac_list, *tac_count)) {
            // Remove the dead code entry
            remove_dead_code(tac_list, tac_count, i);
            i--; // Adjust the index due to the removal
        }
    }

    // Perform Common Subexpression Elimination (CSE)
    for (int i = 0; i < *tac_count; i++) {
        if (is_common_subexpression(tac_list[i], tac_list, *tac_count)) {
            // Replace the current expression with a temporary variable
            char temp[20];
            sprintf(temp, "t%d", i);
            strcpy(tac_list[i].result, temp);
        }
    }
}

// Function to print the TAC list
void print_tac(TAC *tac_list, int tac_count) {
    printf("Optimized TAC:\n");
    for (int i = 0; i < tac_count; i++) {
        printf("%s = %s %s %s\n", tac_list[i].result, tac_list[i].operand1, tac_list[i].operator, tac_list[i].operand2);
    }
}

// Main function to handle file input and call optimization functions
int main() {
    FILE *fp = fopen("tac_input.txt", "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    TAC tac_list[100];
    int tac_count = 0;
    char line[100];

    // Reading input TAC from the file
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);

        // Parsing TAC expression (assuming the format is: result = operand1 operator operand2)
        if (strlen(line) == 0) continue;
        
        // Splitting the line into components
        sscanf(line, "%s = %s %s %s", tac_list[tac_count].result, tac_list[tac_count].operand1, tac_list[tac_count].operator, tac_list[tac_count].operand2);
        tac_count++;
    }

    fclose(fp);

    // Optimize the TAC by applying Dead Code Elimination and Common Subexpression Elimination
    optimize_tac(tac_list, &tac_count);

    // Print the optimized TAC
    print_tac(tac_list, tac_count);

    return 0;
}
