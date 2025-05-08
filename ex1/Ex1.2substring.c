//substring present or not
#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char a[100],b[100];
    int c=0,j=0,i=0;
    printf("Enter the main string :");
    scanf("%[^\n]%*c", a);
    printf("Enter the string to search:");
    scanf("%[^\n]%*c", b);
        while(i<strlen(a)&&j<strlen(b)){
            if(a[i]==b[j]){
              i++;               
              j++;               
              c++;
            }
                else{
                j=0;
                i++;
                c=0;
            }
        }
    
    if(c==strlen(b))
    printf("True");
    else
    printf("false");
}
