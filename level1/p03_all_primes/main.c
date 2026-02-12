#include <math.h>
#include <stdio.h>
#include <time.h>
int main() {
    int sum = 0;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for (int i = 2; i <=1000; i++)
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
            printf("%d ", i);
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("\nTime is %f\n", cpu_time_used);
    return 0;
}


