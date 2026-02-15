#include <iostream>

#define n 1000
int pr[n], tot;
bool vis[n+1];

void check_prime( ) {
    vis[0] = vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) pr[++tot] = i;
        for (int j = 1; j <= tot and pr[j] * i <= n; j++) {
            vis[i * pr[j]] = true;
            if (i % pr[j] == 0) break;
        }
    }
}

int main( ) {

    check_prime();
    for (int i = 1; i <= tot; i++) {
        std::cout << pr[i] << " ";
    }
    putchar('\n');
    printf("time cost:%dms",clock());

    return 0;
}
