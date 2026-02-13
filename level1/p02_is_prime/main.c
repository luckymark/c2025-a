#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    unsigned int number;
    printf("Please enter a number:");
    scanf("%u", &number);
    if (number <= 0)
    {
        printf("Invalid Input");
        system("pause");
        return 1;
    }
    if (number == 1)
    {
        printf("%d is not prime(1 is neither  a prime nor a composite number)\n", number);
        system("pause");
        return 0;
    }

    int sq = sqrt(number);
    for (int i = 2; i <= sq; i++)
    {
        if (number % i == 0)
        {
            printf("%d is not prime\n", number);
            system("pause");
            return 0;
        }
    }
    printf("%d is prime\n", number);
    system("pause");
    return 0;
}
