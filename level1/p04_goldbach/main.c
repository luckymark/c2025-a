#include <iostream>

#define n 100

bool vis[n+1];
int pr[n], tot;

void get_prime( ) {
    vis[0] = vis[1] = true;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) pr[++tot] = i;
        for (int j = 1; j <= tot and i * pr[j] <= n; j++) {
            vis[i * pr[j]] = true;
            if (i % pr[j] == 0) break;
        }
    }
}


bool check(int x) {
    for (int i = 1; i <= tot and pr[i] < x; i++)
        if (!vis[x - pr[i]]) return true;
    return false;
}

int main( ) {
    get_prime( );
    bool flag = true;
    for (int i = 4; i <= n; i += 2) {
        if (!check(i)) {
            flag = false;
            break;
        }
    }
    if (flag) {printf("Goldbach's Conjecture is true in [1,100]!\n");}
    else {printf("Goldbach's Conjecture is false in [1,100]!\n");}
    return 0;
}
