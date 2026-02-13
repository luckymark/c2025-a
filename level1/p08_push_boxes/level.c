#include "head.h"

int new_level(int level)
{
    if(level==-1)
    {
        return -1;
    }
    //初始化数据
    char score_list[MAX_LEVEL];
    int score = MAX_SCORE;

    FILE *records = try_open("records","r",MAX_LEVEL);
    fread(score_list, sizeof(char), MAX_LEVEL, records);
    fclose(records);
    char score_record = score_list[level];


    char level_name[15*sizeof(char)];
    sprintf(level_name,"levels\\%d.txt",level);
    FILE *stored_map = fopen(level_name,"r");
    char map[MAX_HEIGHT][MAX_WIDTH];
    char target_map[MAX_HEIGHT][MAX_WIDTH];
    //读取地图
    for(int i=0;i<MAX_HEIGHT;i++)
    {
        fscanf(stored_map,"%s",map[i]);
    }
    fclose(stored_map);
    int player_X = 0;
    int player_Y = 0;
    int box_finished =0;
    int box_total = 0;
    //绘制地图
    for(int i=0;i<MAX_HEIGHT;i++)
    {
        for(int j=0;j<MAX_WIDTH;j++)
        {
            gotoxy(j,i);
            switch(map[i][j])
            {
            case '0':
                //空地
                printf(SPACE);
                target_map[i][j] = 0;
                break;
            case '1':
                //墙
                printf(WALL);
                break;
            case '2':
                //箱子
                target_map[i][j] = 0;
                color_print(BOX,COLOR_BOX1);
                box_total++;
                break;
            case '3':
                //目标
                map[i][j] = '0';
                target_map[i][j] = 1;
                color_print(TARGET,COLOR_TARGET);
                break;
            case '4':
                //玩家出生点
                target_map[i][j] = 0;
                map[i][j] = '0';
                color_print(PLAYER,COLOR_PLAYER);
                player_X = j;
                player_Y = i;
                break;
            default:
                break;
            }
        }
    }
    gotoxy(0,MAX_HEIGHT+1);
    printf("当前分数：%d",score);
    gotoxy(0,MAX_HEIGHT+2);
    printf("最高分数：%d",score_list[level]);

    char key;
    int box_color;
    char next_X = 0;
    char next_Y = 0;
    char next_step = FALSE;
    char try_move = FALSE;

    while(1)
    {


        if (kbhit())//按键事件
        {
            key = _getch();//not print at screen
            next_step = FALSE;
            try_move = TRUE;
            switch (key)
            {
            case ESC:
                return -1;//退出
            case 'r':
                return -2;//重开
            case KEY_UP:
                next_X = 0;
                next_Y = -1;
                break;
            case KEY_DOWN:
                next_X = 0;
                next_Y = 1;
                break;
            case KEY_LEFT:
                next_X = -1;
                next_Y = 0;
                break;
            case KEY_RIGHT:
                next_X = 1;
                next_Y = 0;
                break;
            default:
                try_move = FALSE;
                break;
            }

            if (try_move == TRUE)
            {
                switch (map[player_Y + next_Y][player_X + next_X])
                {
                case '1': //面前为墙时
                    break;
                case '0': //面前为空地时
                    next_step = TRUE;
                    gotoxy(player_X, player_Y);
                    if (target_map[player_Y][player_X] == 1)
                    {
                        color_print(TARGET,COLOR_TARGET);
                    }
                    else
                    {
                        printf(SPACE);
                    }
                    gotoxy(player_X + next_X, player_Y + next_Y);
                    color_print(PLAYER,COLOR_PLAYER);
                    player_X = player_X + next_X;
                    player_Y = player_Y + next_Y;
                    break;
                case '2': //面前为箱子
                    if (map[player_Y + 2 * next_Y][player_X + 2 * next_X] == '0') //箱前为空地
                    {
                        next_step = TRUE;
                        if (target_map[player_Y + next_Y][player_X + next_X] == 1) //出目标点
                        {
                            box_finished--;
                        }
                        if (target_map[player_Y + 2 * next_Y][player_X + 2 * next_X] == 1) //入目标点
                        {
                            box_finished++;
                            box_color = COLOR_BOX2;
                        }
                        else
                        {
                            box_color = COLOR_BOX1;
                        }
                        gotoxy(player_X, player_Y);
                        if (target_map[player_Y][player_X] == 1)
                        {
                            color_print(TARGET,COLOR_TARGET);
                        }
                        else
                        {
                            printf(SPACE);
                        }


                        gotoxy(player_X + next_X, player_Y + next_Y);
                        color_print(PLAYER,COLOR_PLAYER);

                        gotoxy(player_X + 2 * next_X, player_Y + 2 * next_Y);
                        color_print(BOX, box_color);


                        map[player_Y + next_Y][player_X + next_X] = '0';
                        map[player_Y + 2 * next_Y][player_X + 2 * next_X] = '2';
                        player_X = player_X + next_X;
                        player_Y = player_Y + next_Y;
                    }
                default:
                    break;
                }
            }
            if (score)
            {
                score -= next_step;
            }
            if (box_finished == box_total)
            {
                if (score > score_record)
                {
                    score_list[level] = score;
                    records = try_open("records", "wb",MAX_LEVEL);
                    fwrite(score_list, sizeof(char), MAX_LEVEL, records);
                    fclose(records);
                }
                char title[32];
                snprintf(title,NAME_LENGTH,"Level finished! Your score: %d",score);
                Sleep(500);
                return menu((char*[]){"下一关卡", "返回首页", "关卡列表"}, 3, title);
            }
            gotoxy(10,MAX_HEIGHT + 1);
            printf("%d ", score);
            gotoxy(10,MAX_HEIGHT + 2);
            printf("%d ", score_record);

        }
    }
}

