#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void code(char* Target){
    for(size_t i=0;i<strlen(Target);i++){
        Target[i]+=1;
        printf("%c",Target[i]);
    }
    printf("\n");
}
void decode(char* Target){
    for(size_t i=0;i<strlen(Target);i++){
        Target[i]-=1;
        printf("%c",Target[i]);
    }
    printf("\n");
}
int main(){
    char* target=(char*)malloc(sizeof(char)*10);
    gets(target);
    while(1){
        int a;
        printf("Please choose coding(0) or decoding(1)\n");
        scanf("%d",&a);
        if(a==0){
            code(target);
        }else if(a==1){
            decode(target);
        }else{
            continue;
        }
    }
    return 0;
}
