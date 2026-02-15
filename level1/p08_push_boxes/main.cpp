#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

constexpr int LEN = 110;

int n = 21;
struct POS {
    int x, y;
    bool operator==(const POS &p) const {
        return x == p.x && y == p.y;
    }
};
mt19937 rad(time(0));
POS ed, now;
int num;
int vis[LEN][LEN];

void build( ) {
    num = rad( ) % 5 + 1;
    int t = num;
    while (t--) {
        int x = rad( ) % n + 1, y = rad( ) % n + 1;
        vis[x][y] = 1;
    }
    vis[n - 1][n] = 2;
}
void output( ){
    system("cls");
    for(int i = 1; i <= n; i++, cout << endl)
        for(int j = 1; j <= n; j++){
            if(i == now.x and j == now.y) cout << 'P';
            else if(vis[i][j] == 1) cout << '#';
            else if(vis[i][j] == 2) cout << 'E';
            else cout << '.';
            cout << " ";
        }
    return;
}
bool check(int x, int y){
    if(x >= 1 and y >= 1 and x <= n and y <= n) return 1;
    return 0;
}

int main( ){

    build( );
    now = (POS){1, 1};
    cout << "Please use 'WASD' to move......\nPress any key to continue......";
    if(getch( )) output( );

    char ch;
    while (num) {
        ch = getch( );
        bool flag = false;
        if (ch == 'w' and check(now.x - 1, now.y)){
            if(vis[now.x-1][now.y] == 1){
                if(check(now.x-2, now.y) and vis[now.x-2][now.y] != 1){
                    vis[now.x-1][now.y] = 0;
                    if(vis[now.x-2][now.y] == 2) num--;
                    else vis[now.x-2][now.y] = 1;
                    now.x--;
                }
            }
            else now.x--;
        }
        else if (ch == 'a' and check(now.x, now.y - 1)){
            if(vis[now.x][now.y-1] == 1){
                if(check(now.x, now.y-2) and vis[now.x][now.y-2] != 1){
                    vis[now.x][now.y-1] = 0;
                    if(vis[now.x][now.y-2] == 2) num--;
                    else vis[now.x][now.y-2] = 1;
                    now.y--;
                }
            }
            else now.y--;
        }
        else if (ch == 's' and check(now.x + 1, now.y)){
            if(vis[now.x+1][now.y] == 1){
                if(check(now.x+2, now.y) and vis[now.x+2][now.y] != 1){
                    vis[now.x+1][now.y] = 0;
                    if(vis[now.x+2][now.y] == 2) num--;
                    else vis[now.x+2][now.y] = 1;
                    now.x++;
                }
            }
            else now.x++;
        }
        else if (ch == 'd' and check(now.x, now.y + 1)){
            if(vis[now.x][now.y+1] == 1){
                if(check(now.x, now.y+2) and vis[now.x][now.y + 2] != 1){
                    vis[now.x][now.y+1] = 0;
                    if(vis[now.x][now.y+2] == 2) num--;
                    else vis[now.x][now.y+2] = 1;
                    now.y++;
                }
            }
            else now.y++;
        }
        else flag = true;
        if (flag) cout << "ILLEGAL!!!\n";
        else output( );
    }
    system("cls");
    cout << "YOU WIN!!!\n";
    return 0;
}
