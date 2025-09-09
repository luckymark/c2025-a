#include<stdio.h>
#include<stdbool.h>
int GetPrimeNumber(int Prime_number[],int Prinum){
    for(int i=2;i<101;i++){
        bool pri=true;
        for(int j=2;j<i;j++){
            if(i%j==0){
                pri=false;
            }
        }
        if(pri){
            Prime_number[Prinum]=i;
            Prinum++;
        }
    }
    return Prinum;
}
int main(){
    int prime_number[101]={0},prinum=0;
    prinum=GetPrimeNumber(prime_number,prinum);
    for(int i=2;i<101;i++){
        if(i>2&&i%2==0){
            for(int j=0;j<prinum;j++){
                for(int q=j;q<prinum;q++){
                    if(prime_number[j]+prime_number[q]==i){
                        printf("%d=%d+%d\n",i,prime_number[j],prime_number[q]);
                        goto next;
                    }
                }
            }
        }else if(i>5&&i%2==1){
            for(int j=0;j<prinum;j++){
                for(int q=j;q<prinum;q++){
                    for(int w=q;w<prinum;w++){
                        if(i==prime_number[j]+prime_number[q]+prime_number[w]){
                            printf("%d=%d+%d+%d\n",i,prime_number[j],prime_number[q],prime_number[w]);
                            goto next;
                        }
                    }
                }
            }
        }
        next: ;
    }
    return 0;
}
