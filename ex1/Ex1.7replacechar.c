#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char a[100],b,c;
    printf("Enter the string1 :");
    scanf("%[^\n]%*c", a);
    printf("Enter the char to be replaced for :");
    scanf(" %c", &b);
    printf("Enter the char to be replaced as :");
    scanf(" %c", &c);
    for(int i=0;i<strlen(a);i++)
    if(a[i]==b)
    a[i]=c;
    printf("%s",a);
   }

