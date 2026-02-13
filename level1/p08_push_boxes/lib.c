#include "head.h"


void color_print(char *text,int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color);
    printf(text);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | COLOR_WALL);

}

void gotoxy(int X, int Y)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = X; scrn.Y = Y;
    SetConsoleCursorPosition(hOuput, scrn);
}

FILE *try_open(char *filename, char *mode, int items){

    FILE *fp = fopen(filename,mode);

    if(fp == NULL)
    {
        fp = fopen(filename,"wb");
        char list[items];
        for(int i=0;i<items;i++)
        {
            list[i]=0;
        }
        fwrite(list, items, 1, fp);
        fclose(fp);
        fp = fopen(filename,mode);
    }
    return fp;
}

int menu(char *select[],int len,char *title)
{
    system("cls");
    gotoxy(3,0);
    printf(title);
    int index = 0;
    char ch;
    gotoxy(3, 2);
    printf("enter ↑ ↓ to control system");
    for (int i = 0; i < len; i++) {
        gotoxy(5, 3 + i);
        printf(select[i]);
    }
    gotoxy(3, 3);
    printf("%s%s",CHOOSING,select[0]);

    while (1) {
        if (kbhit()) {
            ch = _getch();//not print at screen

            switch (ch)
            {
            case ESC:
                return -1;
            case KEY_UP:
                gotoxy(3, 3 + index);
                printf("  %s ",select[index]);
                index--;
                break;
            case KEY_DOWN:
                gotoxy(3, 3 + index);
                printf("  %s ",select[index]);
                index++;
                break;
            default:
                break;
            }
            if (index < 0) {
                index = len - 1;
            }
            else if (index >= len) {
                index = 0;
            }

            gotoxy(3, 3 + index);
            printf("%s%s",CHOOSING,select[index]);
            if (ch == '\r') {
                system("cls");
                gotoxy(0,0);
                return index;
            }
        }
    }
}
