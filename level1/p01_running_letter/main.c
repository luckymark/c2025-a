#include <stdio.h>
#include <windows.h>
#include <string.h>
#define MAXLEN 100
//#define DEBUG
enum DIR{forward=0, backward};

int GetWidth(HANDLE hd,CONSOLE_SCREEN_BUFFER_INFO csbi);


int main() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == NULL) {
        printf("GetConsoleWindow failed!\n");
        system("pause");
        return 1;
    }
    CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;

    char word[MAXLEN] = "\0";
    scanf("%s", word);

    char space[MAXLEN] = "\0";
    int len = strlen(word);

    enum DIR direction = forward;
    int width = 0;

    while (1) {
        system("cls");

        width = GetWidth(handle, ScreenInfo);
#ifdef DEBUG
        printf("%d",width);
        system("pause");
#endif
        if (width==0) {
            printf("false");
            system("pause");
            return 1;
        }
        if (width <= len) {
            printf("The window is too narrow!");
            system("pause");
            return 1;
        }

        printf("%s%s", space,word);
        if (strlen(space) + len >= width) {
            direction = backward;
        }
        else if (strlen(space) == 0) {
            direction = forward;
        }
        switch (direction) {
            case 0:
                strcat(space, " ");
                break;
            case 1:
                space[strlen(space)] = 0;
                space[strlen(space) - 1] = '\0';
        }
        _sleep(50);
    }
    return 0;
}
int GetWidth(HANDLE hd,CONSOLE_SCREEN_BUFFER_INFO csbi) {
    GetConsoleScreenBufferInfo(hd, &csbi);
    return csbi.dwSize.X;
}