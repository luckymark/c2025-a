#include <iostream>

int main( ) {
    while (1) {
        for (int i = 1; i <= 127; i++) {
            for (int j = 0; j < i; j++){
                putchar(' ');
            }
            putchar('a');
            system("cls");
        }
        for (int i = 1; i <= 127; i++) {
            for (int j = 0; j < 127 - i; j++) {
                putchar(' ');
            }
            putchar('a');
            system("cls");
        }
    }
    return 0;
}
