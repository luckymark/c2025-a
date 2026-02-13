#include <stdio.h>
#include <windows.h>

# define MAX 1000
char list[MAX-1];

int main(void) {
    DWORD stop;
    DWORD start = GetTickCount();
    for (int i = 2; i < MAX; i++) {
        if (list[i-1]==0) {
            for (int j = i*i; j < MAX; j+=i) {
                list[j-1] = 1;
            }
        }

    }
    for (int i = 2; i < MAX; i++) {
        if (list[i-1]==0) {
            printf("%d\n", i);
        }
    }
    stop = GetTickCount();
    printf("time: %lld ms\n", stop - start);
    system("pause");
    return 0;
}
