#include <math.h>
#include <stdio.h>
#include <time.h>
int main() {
    int sum = 0;
    int j=0;
    int PrimeNumber[26];//100以内的素数有25个
    int test;
    int evenSuccess=0;//忽略2的影响
    for (int i = 2; i <=100; i++)
    {
        sum=0;
        int result = (int)sqrt(i);
        for (int j = 2; j <= result; j++)
        {
            if (i % j == 0)
            {
                sum++;
                break;
            }
        }
        if (sum==0)
        {
            PrimeNumber[j]=i;
            j++;
        }
    }
    for(int i=2;i<=50;i++)
    {
        int even=2*i;
        for(int h=0;h<26;h++)
        {
            if(PrimeNumber[h]<even&&PrimeNumber[h+1]>even)
            {
                test=h;
                break;
            }
        }
        for(int a=0;a<test;a++)
        {
            if(even=PrimeNumber[a]+PrimeNumber[test-a])
            {
                evenSuccess++;
                break;
            }
        }
    }
    printf("下面会输出成功的次数\n");
    printf("%d\n",evenSuccess);
    if(evenSuccess==49)
    {
        printf("因为100里除2有49个偶数,所以强歌德巴赫猜想正确\n");
        printf("因为大于5的奇数减3变成大于2的偶数，所以弱歌德巴赫猜想自然正确\n");
    }
    else("无法证明歌德巴赫猜想正确");

    return 0;
}