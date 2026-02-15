//The code only apply for string consisting of letters whose ASCLL code between 33 and 128
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

int a[200], b[200];
mt19937_64 rad(time(0));

//An easy encode measure:randomly replace a letter with another
void precode( ) {
    for (int i = 33; i <= 126; i++) a[i] = i;
    shuffle(a + 33, a + 126 + 1, rad);
    for (int i = 33; i <= 126; i++) b[a[i]] = i;
}
string encode(string s) {
    for (int i = 0; i < (int)s.size( ); i++) {
        int j = s[i];
        cout << j << " ";
        s[i] = (char)a[j];
    }
    cout << endl;
    return s;
}
string decode(string s) {
    for (int i = 0; i < (int)s.size( ); i++) {
        int j = s[i];
        s[i] = (char)b[j];
    }
    return s;
}

int main( ) {
    precode();

    string s;
    cin >> s;
    s = encode(s);
    cout << "the string after encode: " << s << endl;
    s = decode(s);
    cout << "the string after decode: " << s << endl;
    return 0;
}
// test data: !@#$%^&*()qwertyuiop231567865ASDFGHJK
