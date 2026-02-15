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
POS bg, ed;
namespace Build_Map {
    int dx[5] = {0, 1, -1, 0, 0};
    int dy[5] = {0, 0, 0, -1, 1};
    int vis[LEN][LEN];
    bool way[LEN][LEN];
    bool gotit;
    bool ok(int x, int y) {
        if (x < 1 or x > n or y < 1 or y > n) return 0;
        if (!vis[x][y]) return 0;
        return 1;
    }
    void dfs(int x, int y) {
        if ((POS){x, y} == ed) {
            gotit = 1;
            return;
        }
        int a[4] = {1, 2, 3, 4};
        shuffle(a + 0, a + 5, rad);
        way[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[a[i]] * 2, ty = y + dy[a[i]] * 2;
            int ax = x + dx[a[i]], ay = y + dy[a[i]];
            if (ok(tx, ty) and !vis[ax][ay] and !way[tx][ty]) {
                vis[ax][ay] = 1;
                dfs(tx, ty);
            }
            if (gotit) break;
        }
        return;
    }
    void fuction( ) {
        for (int i = 1; i <= n; i += 2)
            for (int j = 1; j <= n; j += 2)
                vis[i][j] = 1;
        bg = (POS){1, 1};
        ed = (POS){n, n};
        dfs(1, 1);
        gotit = 0;
        dfs(1, n);
        gotit = 0;
        dfs(n, 1);
    }
};
using Build_Map::vis;
void output(POS now) {
    system("cls");
    for (int i = 0; i <= n + 1; i++, cout << endl) {
        for (int j = 0; j <= n + 1; j++) {
            if ((POS){i, j} == now) cout << "P";
            else if ((POS){i, j} == bg) cout << "B";
            else if ((POS){i, j} == ed) cout << "E";
            else if (vis[i][j]) cout << '.';
            else cout << '#';
            cout << " ";
        }
    }
}
bool check(int x, int y) {
    return (x >= 1 and y >= 1 and x <= n and y <= n and vis[x][y]);
}
int main( ){
    Build_Map::fuction( );

    cout << "Please use 'WASD' to move......\nPress any key to continue......";

    POS now = bg;
    if (getch( )) output(now);

    char ch;
    while (!(now == ed)) {
        ch = getch( );
        bool flag = false;
        if (ch == 'w' and check(now.x - 1, now.y)) now.x--;
        else if (ch == 'a' and check(now.x, now.y - 1)) now.y--;
        else if (ch == 's' and check(now.x + 1, now.y)) now.x++;
        else if (ch == 'd' and check(now.x, now.y + 1)) now.y++;
        else flag = true;
        if (flag) cout << "ILLEGAL!!!\n";
        else output(now);
    }
    system("cls");
    cout << "YOU WIN!!!\n";
    return 0;
}
