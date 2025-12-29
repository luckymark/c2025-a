#include "input_storage.h"
#include <stdio.h>
#include <string.h>

#define SAVE_FILE  "gomoku.sav"
void save_game(void)
{
    FILE *fp = fopen(SAVE_FILE, "w");
    if (!fp) { perror("save_game"); return; }

    fprintf(fp, "%d %d %d\n", game.turn ? 1 : 0, game.game_over ? 1 : 0, game.winner);
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x)
            fprintf(fp, "%d ", game.board[x][y]);
        fputc('\n', fp);
    }
    fclose(fp);
    printf("进度已保存 → %s\n", SAVE_FILE);
}

bool load_game(void)
{
    FILE *fp = fopen(SAVE_FILE, "r");
    if (!fp) { printf("未发现存档，将开始新游戏\n"); return false; }

    int b, g, w;
    if (fscanf(fp, "%d %d %d\n", &b, &g, &w) != 3){
        fclose(fp);
        printf("存档损坏，将开始新游戏\n");
        return false;
    }
    game.turn = b;
    game.game_over  = g;
    game.winner     = w;

    for (int y = 0; y < BOARD_SIZE; ++y)
    {
        for (int x = 0; x < BOARD_SIZE; ++x){
            if (fscanf(fp, "%d", &game.board[x][y]) != 1)
            {
                fclose(fp);
                printf("存档损坏，将开始新游戏\n");
                return false;
            }
        }
    }
    fclose(fp);
    printf("进度已从 %s 加载\n", SAVE_FILE);
    return true;
}