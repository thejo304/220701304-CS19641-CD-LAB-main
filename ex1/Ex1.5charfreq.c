#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char a[100];
    int f[256]={0};
    printf("Enter the string1 :");
    scanf("%[^\n]%*c", a);
    for(int i=0;i<strlen(a);i++)
        f[(unsigned char)a[i]]++;
    for(int i=0;i<256;i++)
        if(f[i]>0)
        printf("%c-%d\n",(char)i,f[i]);
   }

