#include "head.h"

int main()
{
    int choice;
    int level = 0;
    char *main_menu[] = { "从头开始","选择关卡","退出游戏" };
    char *level_list[MAX_LEVEL];
    char score_list[MAX_LEVEL];
    FILE *records;

    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; // 隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    while (1)
    {
        home:
        choice = menu(main_menu,3,"推箱子");
        switch (choice)
        {
        case -1:
        case 2:
            return 0;
        case 0:
            level = 0;
            break;
        case 1:
            level_list:

            records = try_open("records","r",MAX_LEVEL);
            fread(score_list, sizeof(char), MAX_LEVEL, records);
            fclose(records);
            for (char i = 0; i < MAX_LEVEL; i++)
            {
                level_list[i] = (void *)malloc(NAME_LENGTH*sizeof(char));
                snprintf(level_list[i],NAME_LENGTH,"第%d关 最高分：%d",i+1,score_list[i]);

            }
            level = menu(level_list,MAX_LEVEL,"关卡列表：");
            for (char i = 0; i < MAX_LEVEL; i++)
            {
                free(level_list[i]);
                level_list[i] = NULL;
            }

        default:
            break;
        }

        next_level:
        switch (new_level(level))
        {
            case -1:
            case 1:
                goto home;
            case 0:
                level++;
            case -2:
                goto next_level;
            case 2:
                goto level_list;
            default:
                return -1;
        }

    }
}

