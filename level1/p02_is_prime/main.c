#include <iostream>
#include <cmath>

int main( ) {
    int n;
    std::cin >> n;
    if (!(n & 1)) {
        printf("%d is not a prime!\n",n);
        return 0;
    }
    int ub = sqrt(n);
    for (int i = 2; i <= ub; i++) {
        if (n % i == 0) {
            printf("%d is not a prime!\n",n);
            return 0;
        }
    }
    printf("%d is a prime!\n",n);

    return 0;
}
