
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "input_storage.h"
#define BOARD_SIZE 15
#define CELL_SIZE 40
#define BOARD_MARGIN 50
#define STATUS_WIDTH 250
#define WINDOW_WIDTH (BOARD_SIZE * CELL_SIZE + 2 * BOARD_MARGIN + STATUS_WIDTH)
#define WINDOW_HEIGHT (BOARD_SIZE * CELL_SIZE + 2 * BOARD_MARGIN)
#define STONE_RADIUS (CELL_SIZE / 2 - 2)

#ifdef __cplusplus
exteern "C" {
#endif
    typedef struct GameStatues
    {
        int board[BOARD_SIZE][BOARD_SIZE];
        int turn;
        bool game_over;
        int winner;
    } GameStatues;
    extern  GameStatues game;

    TTF_Font* LoadFont();
    void reset_game();
    void FirstMove();
    bool check_win(int x, int y, int player);
    void handle_click(int x,int y);

    bool init_Sdl(SDL_Window** window,  SDL_Renderer** renderer,TTF_Font** font);

    void draw_board_process(SDL_Renderer* renderer,TTF_Font* font );
    void draw_board(SDL_Renderer* renderer);
    void draw_stones(SDL_Renderer* renderer);
    void draw_chinese_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
    void draw_status_panel(SDL_Renderer* renderer, TTF_Font* font);

    void delete_board_process(SDL_Window* window,SDL_Renderer* renderer, TTF_Font* font);

#ifdef __cplusplus
}
#endif

#endif /* __BLUETOOTH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
