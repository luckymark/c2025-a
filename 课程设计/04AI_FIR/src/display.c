#include "display.h"

//棋盘状态：0=空，1黑棋，2=白棋
GameStatues game = {
    .board ={0},
    .turn =0,
    .game_over=false,
    .winner=0
};
//随机先手
void FirstMove()
{
    srand(time(NULL));
    int random = (rand() % 100)%2;
    if(random == 0)
    {
        game.turn = 1;
    }
    else
    {
        game.turn = 2;
    }
}

//尝试加载中文
TTF_Font* LoadFont()
{
    const char* font_paths[] = {
        "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",           // 文泉驿微米黑
        "/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",            // 文泉驿正黑
        "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",  // Noto字体
        "/usr/share/fonts/truetype/arphic/ukai.ttc",               // AR PL UKai
        "/usr/share/fonts/truetype/arphic/uming.ttc",              // AR PL UMing
        "/usr/share/fonts/truetype/droid/DroidSansFallback.ttf",   // Droid Sans Fallback
        NULL
    };

    for (int i = 0; font_paths[i] != NULL; i++)
    {
        TTF_Font* font = TTF_OpenFont(font_paths[i], 20);
        if (font  !=  NULL)
        {
            printf("成功加载中文字体: %s\n", font_paths[i]);
            return font;
        }
    }
    printf("警告：无法加载任何字体\n");
    return NULL;
}

//初始化SDL和TTF
bool init_Sdl(SDL_Window** window,  SDL_Renderer** renderer,TTF_Font** font)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf("TTF could not initialize! SDL Error: %s\n", TTF_GetError());
        return false;
    }

    *font = LoadFont();

    *window = SDL_CreateWindow("五子棋游戏",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (*window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

//绘制棋盘
void draw_board(SDL_Renderer* renderer)
{
    //设置背景
    SDL_SetRenderDrawColor(renderer, 220, 179, 92, 255);
    SDL_Rect board_rect = {0, 0, BOARD_SIZE * CELL_SIZE + 2 * BOARD_MARGIN, WINDOW_HEIGHT};  //设置界面大小
    SDL_RenderFillRect(renderer, &board_rect);

    //绘制网格
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i =0; i < BOARD_SIZE; i++)
    {
        SDL_RenderDrawLine(renderer,
                  BOARD_MARGIN,
                  BOARD_MARGIN + i * CELL_SIZE,
                  BOARD_MARGIN + (BOARD_SIZE - 1) * CELL_SIZE,
                  BOARD_MARGIN + i * CELL_SIZE);

        SDL_RenderDrawLine(renderer,
                          BOARD_MARGIN + i * CELL_SIZE,
                          BOARD_MARGIN,
                          BOARD_MARGIN + i * CELL_SIZE,
                          BOARD_MARGIN + (BOARD_SIZE - 1) * CELL_SIZE);
    }

    //绘制棋盘上的五个点
    int dots[5][2] = {{3, 3}, {3, 11}, {7, 7}, {11, 3}, {11, 11}};
    for (int i = 0; i < 5; i++) {
        int x = BOARD_MARGIN + dots[i][0] * CELL_SIZE;
        int y = BOARD_MARGIN + dots[i][1] * CELL_SIZE;

        // 绘制小圆点
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int dx = -3; dx <= 3; dx++) {
            for (int dy = -3; dy <= 3; dy++) {
                if (dx*dx + dy*dy <= 9) { // 半径为3的圆
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }
}

// 绘制棋子
void draw_stones(SDL_Renderer* renderer) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game.board[i][j] != 0) {
                int x = BOARD_MARGIN + i * CELL_SIZE;
                int y = BOARD_MARGIN + j * CELL_SIZE;

                if (game.board[i][j] == 1) { // 黑棋
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } else { // 白棋
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }

                // 绘制圆形棋子
                for (int dx = -STONE_RADIUS; dx <= STONE_RADIUS; dx++) {
                    for (int dy = -STONE_RADIUS; dy <= STONE_RADIUS; dy++) {
                        if (dx*dx + dy*dy <= STONE_RADIUS*STONE_RADIUS) {
                            SDL_RenderDrawPoint(renderer, x + dx, y + dy);
                        }
                    }
                }

                // 为白棋添加黑色边框
                if (game.board[i][j] == 2) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    for (int r = STONE_RADIUS; r <= STONE_RADIUS + 1; r++) {
                        for (int angle = 0; angle < 360; angle += 2) {
                            int bx = x + r * cos(angle * M_PI / 180);
                            int by = y + r * sin(angle * M_PI / 180);  //利用极坐标来表示边框
                            SDL_RenderDrawPoint(renderer, bx, by);
                        }
                    }
                }
            }
        }
    }
}

// 检查是否获胜
bool check_win(int x, int y, int player) {
    // 检查方向：水平、垂直、左上到右下、右上到左下
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int count = 1;              // 当前位置已经有一个棋子

        // 正向检查
        for (int i = 1; i < 5; i++) {
            int nx = x + i * dx;
            int ny = y + i * dy;
            if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && game.board[nx][ny] == player) {
                count++;
            } else {
                break;
            }
        }

        // 反向检查
        for (int i = 1; i < 5; i++) {
            int nx = x - i * dx;
            int ny = y - i * dy;
            if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && game.board[nx][ny] == player) {
                count++;
            } else {
                break;
            }
        }

        if (count >= 5) {
            return true;
        }
    }

    return false;
}
//重启游戏
void reset_game()
{
    memset(game.board, 0, sizeof(game.board));
    game.turn =0;
    game.game_over = false;
    game.winner = 0;
    printf("游戏已重置");
}

//处理鼠标
void handle_click(int x,int y)
{
    if (game.game_over)
    {
        return;
    }

    //转化坐标
    int board_x = (x-BOARD_MARGIN+CELL_SIZE/2)/CELL_SIZE;
    int board_y = (y-BOARD_MARGIN+CELL_SIZE/2)/CELL_SIZE;

    //检查是否在棋盘范围内
    if (board_x >= 0&& board_x < BOARD_SIZE && board_y >= 0 && board_y < BOARD_SIZE)
    {
        if (game.board[board_x][board_y] ==0)
        {
            game.board[board_x][board_y] = game.turn ? 1 : 2;

            if (check_win(board_x,board_y,game.board[board_x][board_y]))
            {
                game.game_over = true;
                game.winner =game.board[board_x][board_y];
            }else
            {
                game.turn = 3 - game.turn;

            }
        }
    }
}

//绘制中文文本
void draw_chinese_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    // 使用UTF-8编码渲染中文字符
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    if (surface == NULL) {
        printf("文本渲染失败: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// 绘制状态面板
void draw_status_panel(SDL_Renderer* renderer, TTF_Font* font) {
    int panel_x = BOARD_SIZE * CELL_SIZE + 2 * BOARD_MARGIN;

    // 绘制状态面板背景
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_Rect panel_rect = {panel_x, 0, STATUS_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &panel_rect);

    // 绘制边框
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(renderer, &panel_rect);

    SDL_Color black_color = {0, 0, 0, 255};
    SDL_Color red_color = {255, 0, 0, 255};
    SDL_Color blue_color = {0, 0, 255, 255};
    SDL_Color green_color = {0, 128, 0, 255};

    // 游戏标题
    draw_chinese_text(renderer, font, "五子棋游戏", panel_x + 20, 30, green_color);

    // 分隔线
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawLine(renderer, panel_x + 10, 70, panel_x + STATUS_WIDTH - 10, 70);

    // 游戏状态
    draw_chinese_text(renderer, font, "游戏状态：", panel_x + 20, 80, black_color);
    if (game.game_over) {
        draw_chinese_text(renderer, font, game.winner == 1 ? "黑棋获胜！" : "白棋获胜！",
                         panel_x + 20, 110, red_color);
    } else {
        draw_chinese_text(renderer, font, "对局进行中", panel_x + 20, 110, blue_color);
    }

    // 当前回合
    draw_chinese_text(renderer, font, "当前回合：", panel_x + 20, 150, black_color);
    if (!game.game_over) {
        draw_chinese_text(renderer, font, game.turn ? "黑棋" : "白棋",
                         panel_x + 20, 180, game.turn ? black_color : blue_color);
    } else {
        draw_chinese_text(renderer, font, "游戏结束", panel_x + 20, 180, red_color);
    }

    // 分隔线
    SDL_RenderDrawLine(renderer, panel_x + 10, 220, panel_x + STATUS_WIDTH - 10, 220);

    // 操作说明
    draw_chinese_text(renderer, font, "操作说明：", panel_x + 20, 240, black_color);
    draw_chinese_text(renderer, font, "点击棋盘放置棋子", panel_x + 20, 270, black_color);
    draw_chinese_text(renderer, font, "黑棋先行", panel_x + 20, 300, black_color);
    draw_chinese_text(renderer, font, "ESC键退出游戏", panel_x + 20, 330, black_color);
    draw_chinese_text(renderer, font, "R键重新开始", panel_x + 20, 360, black_color);
    draw_chinese_text(renderer, font, "s键保存进度", panel_x + 20, 600, black_color);
    draw_chinese_text(renderer, font, "L键加载进度", panel_x + 20, 630, black_color);

    // 分隔线
    SDL_RenderDrawLine(renderer, panel_x + 10, 400, panel_x + STATUS_WIDTH - 10, 400);

    // 棋子示例
    draw_chinese_text(renderer, font, "棋子示例：", panel_x + 20, 420, black_color);

    // 黑棋示例
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int dx = -STONE_RADIUS; dx <= STONE_RADIUS; dx++) {
        for (int dy = -STONE_RADIUS; dy <= STONE_RADIUS; dy++) {
            if (dx*dx + dy*dy <= STONE_RADIUS*STONE_RADIUS) {
                SDL_RenderDrawPoint(renderer, panel_x + 40 + dx, 460 + dy);
            }
        }
    }
    draw_chinese_text(renderer, font, "黑棋", panel_x + 60, 455, black_color);

    // 白棋示例
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int dx = -STONE_RADIUS; dx <= STONE_RADIUS; dx++) {
        for (int dy = -STONE_RADIUS; dy <= STONE_RADIUS; dy++) {
            if (dx*dx + dy*dy <= STONE_RADIUS*STONE_RADIUS) {
                SDL_RenderDrawPoint(renderer, panel_x + 40 + dx, 510 + dy);
            }
        }
    }
    // 白棋边框
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int r = STONE_RADIUS; r <= STONE_RADIUS + 1; r++) {
        for (int angle = 0; angle < 360; angle += 2) {
            int bx = panel_x + 40 + r * cos(angle * M_PI / 180);
            int by = 510 + r * sin(angle * M_PI / 180);
            SDL_RenderDrawPoint(renderer, bx, by);
        }
    }
    draw_chinese_text(renderer, font, "白棋", panel_x + 60, 505, black_color);
}

//绘制界面函数
void draw_board_process(SDL_Renderer* renderer,TTF_Font* font )
{
    draw_board(renderer);
    draw_stones(renderer);
    draw_status_panel(renderer, font);
    SDL_RenderPresent(renderer);
}

//清除界面指针
void delete_board_process(SDL_Window* window,SDL_Renderer* renderer, TTF_Font* font)
{
    if (font != NULL) {
        TTF_CloseFont(font);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}