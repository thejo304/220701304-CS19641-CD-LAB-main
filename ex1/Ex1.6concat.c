#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char a[100],b[100];
    printf("Enter the string1 :");
    scanf("%[^\n]%*c", a);
    printf("Enter the string2 :");
    scanf("%[^\n]%*c", b);
        strcat(a,b);
        printf("%s",a);
   }

