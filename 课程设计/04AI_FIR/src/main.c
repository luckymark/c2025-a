#include "display.h"
#include "ai_judge.h"

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    if (!init_Sdl(&window, &renderer, &font)) {
        return -1;
    }
    reset_game();
    FirstMove();
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                } else if (e.key.keysym.sym == SDLK_r) {
                    reset_game();
                    FirstMove();
                } else if (e.key.keysym.sym == SDLK_s) {
                    save_game();
                } else if (e.key.keysym.sym == SDLK_l) {
                    load_game();
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    if (game.turn != 2) {
                        handle_click(e.button.x, e.button.y);
                    }
                }
            }
        }
        draw_board_process(renderer, font);

        if (!game.game_over && game.turn == 2) {
            ai_move();
            SDL_Delay(500);
        }
        draw_board_process(renderer, font);
        SDL_Delay(16);
    }
    delete_board_process(window, renderer, font);
    printf("游戏结束！\n");
    return 0;
}