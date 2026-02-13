#ifndef C2025_CHALLENGE_HEAD_H
#define C2025_CHALLENGE_HEAD_H
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define NAME_LENGTH 30

#define ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define MAX_SCORE 100
#define MAX_LEVEL 5

#define MAX_WIDTH 10
#define MAX_HEIGHT 10

#define CHOOSING "-> "

#define PLAYER "+"
#define SPACE  " "
#define WALL   "#"
#define BOX    "@"
#define TARGET "*"

#define COLOR_WALL 7
#define COLOR_BOX1 6
#define COLOR_BOX2 2
#define COLOR_TARGET 4
#define COLOR_PLAYER 1

#define TRUE 1
#define FALSE 0

FILE *try_open(char *filename, char *mode, int items);
void gotoxy(int X, int Y);
void color_print(char *text,int color);

int menu(char *select[],int len,char *title);
int new_level(int level);



#endif //C2025_CHALLENGE_HEAD_H