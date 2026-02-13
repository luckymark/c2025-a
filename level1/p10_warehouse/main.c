#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define CHOOSING "-> "
#define MAX_LENGTH 100

struct Node{
    char *name;
    int number;
    struct Node *next;
};

struct Node *CreateList() {
    return NULL;
}

int insert(struct Node **list, char name[MAX_LENGTH], int number);
int delete(struct Node **list, int index);
struct Node *find(struct Node *list, char name[MAX_LENGTH]);

void display(struct Node *list);
void in_warehouse (struct Node **list, char name[MAX_LENGTH],int number);
void out_warehouse(struct Node **list, char name[MAX_LENGTH],int number);

void save(struct Node *list);
void load(struct Node **list);

void gotoxy(int X, int Y);
int menu(char *select[],int len,char *title);

int main() {
    struct Node *list = CreateList();
    load(&list);
    char name[50];
    int number;
    while (1) {
        switch (menu((char*[]){"显示存货列表","入库","出库","退出程序"},4,"库存管理"))
        {
            case -1:
            case 3: save(list);         return 0;
            case 0: display(list);      break;
            case 1:
                printf("请输入要入库的品类及数量（空格隔开）：");
                scanf("%s %d",name,&number);
                in_warehouse(&list,name,number);
                break;
            case 2:
                printf("请输入要出库的品类及数量（空格隔开）：");
                scanf("%s %d",name,&number);
                out_warehouse(&list,name,number);
                break;
        }
        Sleep(1000);
    }
}

int insert(struct Node **list, char name[MAX_LENGTH], int number) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

    temp->name = (char *)malloc(strlen(name) + 1);
    strcpy(temp->name,name);
    temp->number = number;
    temp->next = *list ;
    *list = temp;
    return 0;
}

int delete(struct Node **list, int index) {//改成二重指针
    struct Node **change = list;
    struct Node **temp1;
    for (int i = 0; i < index; i++) {
        temp1 = change;
        if ((*change)->next == NULL) {
            return 1;
        }
        change = &((*temp1)->next);
    }
    free((*change)->name);
    free(*change);
    *change =(*change)->next ;
    return 0;
}

struct Node *find(struct Node *list, char name[MAX_LENGTH]) {
    for (int i=0; list != NULL;list = list->next,i++) {
        if (list->name == name) {
            return list;
        }
    }
    return NULL;
}

void display(struct Node *list) {
    for (; list != NULL; list = list -> next) {
        printf("%s: %d\n", list -> name,list->number);
    }
    printf("\n");
}

void in_warehouse(struct Node **list, char name[MAX_LENGTH],int number) {
    struct Node *temp = *list;
    for (int i=0; temp != NULL;temp = temp->next,i++) {
        if (strcmp(temp->name,name) == 0) {
            temp->number += number;
            printf("已入库：%s %d件\n现有%d件\n",name,number,temp->number);
            return;
        }
    }
    insert(list,name,number);
    printf("新入库：%s %d件\n",name,number);
}

void out_warehouse(struct Node **list, char name[MAX_LENGTH],int number) {
    struct Node **temp = list;
    for (int i=0; *temp != NULL;temp = &((*temp)->next),i++) {
        if (strcmp((*temp)->name, name) == 0) {
            if ((*temp) -> number < number)
            {
                printf("数量不足！现有%d件" ,(*temp) -> number);

            }
            else if ((*temp) -> number == number)
            {
                delete(list,i);
                printf("%s已全部出库",name);
            }
            else
            {
                (*temp) -> number -= number;
                printf("已出库：%s %d件\n现有%d件\n",name,number,(*temp) -> number);
            }
            return;
        }
    }
    printf("未找到该品类");
}

void save(struct Node *list)
{
    FILE *fp = fopen("save.txt","w");
    for (; list != NULL; list = list->next) {
        fprintf(fp,"\n%s %d",list->name,list->number);
    }
    fclose(fp);
}
void load(struct Node **list)
{
    char name[50];
    int number;
    FILE *fp = fopen("save.txt","r");
    if (fp == NULL) {
        fp = fopen("save.txt","w");
        fclose(fp);
        fp = fopen("save.txt","r");
    }
    struct Node *temp;
    fpos_t position;
    while (fgetc(fp)!=EOF) {
        fscanf(fp,"%s %d", name, &number);
        insert(list,name,number);
    }
    fclose(fp);
}

void gotoxy(int X, int Y)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = X; scrn.Y = Y;
    SetConsoleCursorPosition(hOuput, scrn);
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
