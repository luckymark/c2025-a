#include<stdio.h>
void hanoi(int n,char from,char target,char blank){
     if(n==1){
        printf("%c->%c\n",from,target);
     }else{
        hanoi(n-1,from,blank,target);
        printf("%c->%c\n",from,target);
        hanoi(n-1,blank,target,from);
     }
}
int main(){
    int n;
    scanf("%d",&n);
    hanoi(n,'A','B','C');
    return 0;
}
