#include <stdio.h>
#include <stdlib.h>
int step = 0;

void hanoi(int num,char source, char target, char through, int *step);

int main() {
    printf("请输入层数：");
    int num ;
    scanf_s("%d",&num);
    hanoi(num, 'A', 'B', 'C', &step);
    printf("总步数：%d\n",step);
    system("pause");
    return 0;
}
