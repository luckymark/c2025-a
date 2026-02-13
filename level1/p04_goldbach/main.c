#include <stdio.h>
#include <windows.h>

# define MAX 100

char list[MAX-1];

int main(void) {
    int primes[MAX-1];
    int amount = 0;
    for (int i = 2; i < MAX; i++) {
        if (list[i-1]==0) {
            for (int j = i*i; j < MAX; j+=i) {
                list[j-1] = 1;
            }
        }

    }
    for (int i = 2; i < MAX; i++) {
        if (list[i-1]==0) {
            primes[amount] = i;
            amount++;
        }
    }
    for (int i = 2; i <= MAX; i+=2) {
        for (int j = 0; j < amount; j++) {
            for (int k = 0; k <= j; k++) {
                if (primes[j]+primes[k]==i) {
                    printf("%d=%d+%d\n", i,primes[j],primes[k]);
                    goto Next;
                }
            }

        }
        printf("Fail to divide %d to two primes!\n",i);
        system("pause");
        return 1;
        Next:
    }
    printf("Succeed!\n");
    system("pause");
    return 0;
}
