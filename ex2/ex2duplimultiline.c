#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char a[1000], temp[100];
    char *keywords[] = {"int", "float", "switch", "case", "break", "if", "else"};
    int keywordCount = 7, j = 0;

    printf("Enter the code (end input with '!'):\n");
    scanf(" %[^\!]*c", a);

    int len = strlen(a);
    printf("Length of input: %d\n", len);

    for (int i = 0; i < len; i++) {  
        if (isalpha(a[i]) || a[i] == '_') {
            j = 0;
            while (isalnum(a[i]) || a[i] == '_') {
                temp[j++] = a[i++];
            }
            temp[j] = '\0';
            i--;

            int isKeyword = 0;
            for (int k = 0; k < keywordCount; k++) {
                if (strcmp(temp, keywords[k]) == 0) {
                    printf("%s is a keyword\n", temp);
                    isKeyword = 1;
                    break;
                }
            }

            if (!isKeyword) {
                printf("%s is an identifier\n", temp);
            }
        } 
        else if (strchr(",;(){}", a[i])) {
            printf("%c is a delimiter\n", a[i]);
        } 
        else if (strchr("+-*/%=", a[i])) {
            printf("%c is an operator\n", a[i]);
        } 
        else if (isdigit(a[i])) {
            j = 0;
            while (isdigit(a[i])) {
                temp[j++] = a[i++];
            }
            temp[j] = '\0';
            i--;
            printf("%s is a constant\n", temp);
        }
    }

    return 0;
}
