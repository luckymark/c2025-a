#include <stdio.h>

void hanoi(int num,char source, char target, char through ,int *step) {
    if (num == 1) {
        printf("    %c -> %c\n", source, target);
        (*step) ++;
    }
    else {
        hanoi(num - 1, source, through, target,step);
        printf("    %c -> %c\n", source, target);
        (*step) ++;
        hanoi(num - 1, through, source, target,step);
    }
}