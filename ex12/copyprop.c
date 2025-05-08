#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char result[20];
    char operand1[20];
    char operator[5];
    char operand2[20];
} TAC;

void trim_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Perform copy propagation
void copy_propagation(TAC *tac_list, int *count) {
    for (int i = 0; i < *count; i++) {
        // Check for copy assignment: a = b (no operator)
        if (strcmp(tac_list[i].operator, "") == 0 && strcmp(tac_list[i].operand2, "") == 0) {
            char from[20], to[20];
            strcpy(to, tac_list[i].result);
            strcpy(from, tac_list[i].operand1);

            // Replace all future uses of `to` with `from`
            for (int j = i + 1; j < *count; j++) {
                if (strcmp(tac_list[j].operand1, to) == 0)
                    strcpy(tac_list[j].operand1, from);
                if (strcmp(tac_list[j].operand2, to) == 0)
                    strcpy(tac_list[j].operand2, from);
            }

            // Optionally remove the copy statement (Dead Code Elimination)
            int used = 0;
            for (int j = i + 1; j < *count; j++) {
                if (strcmp(tac_list[j].operand1, to) == 0 || strcmp(tac_list[j].operand2, to) == 0) {
                    used = 1;
                    break;
                }
            }
            if (!used) {
                // Shift all following TAC up
                for (int k = i; k < *count - 1; k++) {
                    tac_list[k] = tac_list[k + 1];
                }
                (*count)--;
                i--; // Stay on the same index after deletion
            }
        }
    }
}

// Display TAC
void print_tac(TAC *tac_list, int count) {
    printf("Optimized TAC:\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(tac_list[i].operator, "") == 0)
            printf("%s = %s\n", tac_list[i].result, tac_list[i].operand1);
        else
            printf("%s = %s %s %s\n", tac_list[i].result, tac_list[i].operand1, tac_list[i].operator, tac_list[i].operand2);
    }
}

int main() {
    FILE *fp = fopen("tac_input.txt", "r");
    if (!fp) {
        printf("Error opening input file!\n");
        return 1;
    }

    TAC tac_list[100];
    int count = 0;
    char line[100];

    // Read TAC from file
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;

        // Check format: a = b or a = b + c
        int tokens = sscanf(line, "%s = %s %s %s",
                            tac_list[count].result,
                            tac_list[count].operand1,
                            tac_list[count].operator,
                            tac_list[count].operand2);
        if (tokens == 2) {  // Copy assignment
            strcpy(tac_list[count].operator, "");
            strcpy(tac_list[count].operand2, "");
        }
        count++;
    }
    fclose(fp);

    // Apply copy propagation
    copy_propagation(tac_list, &count);

    // Print final optimized code
    print_tac(tac_list, count);

    return 0;
}
