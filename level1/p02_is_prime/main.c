#include <stdio.h>
#include <math.h>
int main() {
    int n;
    int sum = 0;
    printf("请输入一个正整数: ");
    scanf("%d",&n);
    if (n<2)
    {
        printf("%d不是素数",n);
        return 0;
    }
    printf("\n");
    int result = (int)sqrt(n);  // 计算平方根
    for (int i = 1; i <= result; i++)
    {
        if (n % i == 0)
        {
            sum++;
        }
    }
    if (sum>1)
    {
        printf("%d不是素数",n);
    }
    else
    {
        printf("%d是素数",n);
    }
    return 0;
}