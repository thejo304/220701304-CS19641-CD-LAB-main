#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char a[100],b[100];
    int j=0,i=0;
    printf("Enter the string1 :");
    scanf("%[^\n]%*c", a);
   for(i=0;i<strlen(a);i++){
       if(a[i]!=' '){
           b[j]=a[i];
           j++;
       }
   }
    
    printf("%s",b);
}
