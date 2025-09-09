#include<stdio.h>
int justice(int Number){
    int whether=1;
    for(int i=2;i<Number;i++){
        if(Number%i==0){
            whether=0;
        }
    }
    return whether;
}
int main(){
    int number;
    scanf("%d",&number);
    if(justice(number)){
        printf("This number is a prime number.\n");
    }else{
        printf("This number is not a prime number.\n");
    }
    return 0;
}
