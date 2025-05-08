#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim_newline(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void generate_assembly(char* line) {
    char result[20], op1[20], op2[20], operator;

    int matched = sscanf(line, "%s = %s %c %s", result, op1, &operator, op2);

    if (matched == 4) {
        // Binary operation (e.g., t0 = a + b)
        if (operator == '+') {
            printf("MOV AX, [%s]\n", op1);
            printf("ADD AX, [%s]\n", op2);
            printf("MOV [%s], AX\n\n", result);
        } else if (operator == '-') {
            printf("MOV AX, [%s]\n", op1);
            printf("SUB AX, [%s]\n", op2);
            printf("MOV [%s], AX\n\n", result);
        } else if (operator == '*') {
            printf("MOV AX, [%s]\n", op1);
            printf("MOV BX, [%s]\n", op2);
            printf("MUL BX\n");
            printf("MOV [%s], AX\n\n", result);
        } else if (operator == '/') {
            printf("MOV AX, [%s]\n", op1);
            printf("MOV DX, 0\n");
            printf("MOV BX, [%s]\n", op2);
            printf("DIV BX\n");
            printf("MOV [%s], AX\n\n", result);
        }
    } else {
        // Simple assignment (e.g., a = t1)
        sscanf(line, "%s = %s", result, op1);
        printf("MOV AX, [%s]\n", op1);
        printf("MOV [%s], AX\n\n", result);
    }
}

int main() {
    FILE* fp = fopen("assem.txt", "r");
    if (!fp) {
        perror("Failed to open tac_input.txt");
        return 1;
    }

    char line[100];
    printf("; 8086 Assembly Code Generated from TAC:\n\n");
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        generate_assembly(line);
    }

    fclose(fp);
    return 0;
}
