#include <iostream>

using namespace std;

void out(int bg, int ed) {
    cout << (bg == 1 ? 'a' : (bg == 2 ? 'b' : 'c'));
    cout << " -> ";
    cout << (ed == 1 ? 'a' : (ed == 2 ? 'b' : 'c'));
    cout << endl;
}

void move(int n, int bg, int ed, int tmp) {
    if (n == 1) {
        out(bg, ed);
        return;
    }
    move(n - 1, bg, tmp, ed);
    out(bg, ed);
    move(n - 1, tmp, ed, bg);
}

int main( ) {

    int n = 0;//n 层汉诺塔
    cin >> n;

    move(n , 1, 2, 3);

    return 0;
}
