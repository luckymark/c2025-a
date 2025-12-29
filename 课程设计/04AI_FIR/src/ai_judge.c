#include "ai_judge.h"
#include <time.h>

typedef struct {
    int five;
    int live_four;
    int sleep_four;
    int live_three;
    int sleep_three;
    int live_two;
    int sleep_two;
} PatternScore;

PatternScore score_table = {
    .five = 1000000,
    .live_four = 100000,
    .sleep_four = 10000,
    .live_three = 10000,
    .sleep_three = 1000,
    .live_two = 1000,
    .sleep_two = 100
};


int evaluate_direction(int x, int y, int dx, int dy, int player) {
    int score = 0;
    int count = 1;
    int block = 0;
    int empty = 0;

    // 正向检查
    for (int k = 1; k <= 4; k++) {
        int nx = x + k * dx;
        int ny = y + k * dy;

        if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) {
            block++;
            break;
        }

        if (game.board[nx][ny] == player) {
            count++;
        } else if (game.board[nx][ny] == 0) {
            empty++;
            break;
        } else {
            block++;
            break;
        }
    }

    // 反向检查
    for (int k = 1; k <= 4; k++) {
        int nx = x - k * dx;
        int ny = y - k * dy;

        if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) {
            block++;
            break;
        }

        if (game.board[nx][ny] == player) {
            count++;
        } else if (game.board[nx][ny] == 0) {
            empty++;
            break;
        } else {
            block++;
            break;
        }
    }

    // 根据棋型评分
    if (count >= 5) return score_table.five;
    if (block == 2) return 0;

    switch (count) {
        case 4:
            if (block == 0) return score_table.live_four;
            if (block == 1) return score_table.sleep_four;
            break;
        case 3:
            if (block == 0) return score_table.live_three;
            if (block == 1) return score_table.sleep_three;
            break;
        case 2:
            if (block == 0) return score_table.live_two;
            if (block == 1) return score_table.sleep_two;
            break;
        case 1:
            if (block == 0) return score_table.sleep_two / 10;
            break;
    }

    return 0;
}

int overall_evaluate() {
    int black_score = 0;
    int white_score = 0;

    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game.board[i][j] != 0) {
                int player = game.board[i][j];

                for (int d = 0; d < 4; d++) {
                    int score = evaluate_direction(i, j, directions[d][0], directions[d][1], player);
                    if (player == 1) {
                        black_score += score;
                    } else {
                        white_score += score;
                    }
                }
                // 位置加分 - 中心位置更有价值
                int center_dist = abs(i - BOARD_SIZE/2) + abs(j - BOARD_SIZE/2);
                int position_bonus = (BOARD_SIZE - center_dist) * 10;

                if (player == 1) {
                    black_score += position_bonus;
                } else {
                    white_score += position_bonus;
                }
            }
        }
    }

    return black_score - white_score;
}

int check_threat(int player) {
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game.board[i][j] == 0) {
                game.board[i][j] = player;

                // 检查是否形成五连
                for (int d = 0; d < 4; d++) {
                    int dx = directions[d][0];
                    int dy = directions[d][1];
                    int count = 1;

                    // 正向
                    for (int k = 1; k < 5; k++) {
                        int ni = i + k * dx;
                        int nj = j + k * dy;
                        if (ni < 0 || ni >= BOARD_SIZE || nj < 0 || nj >= BOARD_SIZE) break;
                        if (game.board[ni][nj] == player) count++;
                        else break;
                    }

                    // 反向
                    for (int k = 1; k < 5; k++) {
                        int ni = i - k * dx;
                        int nj = j - k * dy;
                        if (ni < 0 || ni >= BOARD_SIZE || nj < 0 || nj >= BOARD_SIZE) break;
                        if (game.board[ni][nj] == player) count++;
                        else break;
                    }

                    if (count >= 5) {
                        game.board[i][j] = 0;
                        return 1; // 发现必胜点
                    }
                }

                game.board[i][j] = 0;
            }
        }
    }
    return 0;
}

void get_quality_moves(int moves[][2], int* move_count, int player) {
    *move_count = 0;
    int priority_moves[BOARD_SIZE * BOARD_SIZE][2];
    int normal_moves[BOARD_SIZE * BOARD_SIZE][2];
    int priority_count = 0, normal_count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game.board[i][j] == 0) {
                // 检查这个位置是否形成威胁
                game.board[i][j] = player;
                if (check_win(i, j, player)) {
                    priority_moves[priority_count][0] = i;
                    priority_moves[priority_count][1] = j;
                    priority_count++;
                }
                game.board[i][j] = 0;

                // 检查这个位置是否阻止对方威胁
                int opponent = 3 - player;
                game.board[i][j] = opponent;
                if (check_win(i, j, opponent)) {
                    priority_moves[priority_count][0] = i;
                    priority_moves[priority_count][1] = j;
                    priority_count++;
                }
                game.board[i][j] = 0;
            }
        }
    }

    // 如果没有威胁位置，考虑棋子周围的空位
    if (priority_count == 0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (game.board[i][j] != 0) {
                    // 检查周围3格内的位置
                    for (int dx = -3; dx <= 3; dx++) {
                        for (int dy = -3; dy <= 3; dy++) {
                            int ni = i + dx;
                            int nj = j + dy;
                            if (ni >= 0 && ni < BOARD_SIZE && nj >= 0 && nj < BOARD_SIZE) {
                                if (game.board[ni][nj] == 0) {
                                    // 检查是否已存在
                                    int exists = 0;
                                    for (int k = 0; k < normal_count; k++) {
                                        if (normal_moves[k][0] == ni && normal_moves[k][1] == nj) {
                                            exists = 1;
                                            break;
                                        }
                                    }
                                    if (!exists) {
                                        normal_moves[normal_count][0] = ni;
                                        normal_moves[normal_count][1] = nj;
                                        normal_count++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < priority_count; i++) {
        moves[*move_count][0] = priority_moves[i][0];
        moves[*move_count][1] = priority_moves[i][1];
        (*move_count)++;
    }

    for (int i = 0; i < normal_count; i++) {
        moves[*move_count][0] = normal_moves[i][0];
        moves[*move_count][1] = normal_moves[i][1];
        (*move_count)++;
    }

    // 如果还是没有有效移动，选择中心位置
    if (*move_count == 0) {
        moves[0][0] = BOARD_SIZE / 2;
        moves[0][1] = BOARD_SIZE / 2;
        *move_count = 1;
    }
}


int alpha_beta_search(int depth, int alpha, int beta, int player, time_t start_time) {
    if (depth == 0 || game.game_over) {
        return overall_evaluate();
    }

    if (time(NULL) - start_time >8 ) { // 最多搜索8秒
        return overall_evaluate();
    }

    int moves[BOARD_SIZE * BOARD_SIZE][2];
    int move_count;
    get_quality_moves(moves, &move_count, player);

    if (player == 1) {
        int max_eval = -10000000;

        for (int i = 0; i < move_count; i++) {
            int x = moves[i][0], y = moves[i][1];

            // 落子
            game.board[x][y] = player;
            int eval = alpha_beta_search(depth - 1, alpha, beta, 3 - player, start_time);
            game.board[x][y] = 0;

            if (eval > max_eval) max_eval = eval;
            if (eval > alpha) alpha = eval;
            if (beta <= alpha) break;
        }
        return max_eval;
    } else {
        int min_eval = 10000000;

        for (int i = 0; i < move_count; i++) {
            int x = moves[i][0], y = moves[i][1];

            // 落子
            game.board[x][y] = player;
            int eval = alpha_beta_search(depth - 1, alpha, beta, 3 - player, start_time);
            game.board[x][y] = 0;

            if (eval < min_eval) min_eval = eval;
            if (eval < beta) beta = eval;
            if (beta <= alpha) break;
        }
        return min_eval;
    }
}

void ai_move() {
    if (game.game_over) return;

    time_t start_time = time(NULL);
    int player = game.turn;

    printf("AI思考中...\n");

    if (is_board_empty()) {
        game.board[BOARD_SIZE/2][BOARD_SIZE/2] = player;
        game.turn = 3 - player;
        printf("AI落子: 中心位置\n");
        return;
    }

    int best_score = (player == 1) ? -10000000 : 10000000;
    int best_x = -1, best_y = -1;

    int moves[BOARD_SIZE * BOARD_SIZE][2];
    int move_count;
    get_quality_moves(moves, &move_count, player);


    // 迭代加深搜索
    for (int depth = 2; depth <= 6; depth += 2) {
        printf("搜索深度: %d\n", depth);

        for (int i = 0; i < move_count; i++) {
            int x = moves[i][0], y = moves[i][1];

            // 检查时间
            if (time(NULL) - start_time > 3) break;

            // 落子
            game.board[x][y] = player;
            int score = alpha_beta_search(depth - 1, -10000000, 10000000, 3 - player, start_time);
            game.board[x][y] = 0;

            // 更新最佳选择
            if (player == 1) {
                if (score > best_score) {
                    best_score = score;
                    best_x = x;
                    best_y = y;
                }
            } else {
                if (score < best_score) {
                    best_score = score;
                    best_x = x;
                    best_y = y;
                }
            }
        }

        if (abs(best_score) > 500000) break;
    }

    // 执行最佳走法
    if (best_x != -1 && best_y != -1) {
        game.board[best_x][best_y] = player;

        if (check_win(best_x, best_y, player)) {
            game.game_over = true;
            game.winner = player;
            printf("AI获胜！位置: (%d, %d)\n", best_x, best_y);
        } else {
            game.turn = 3 - player;
            printf("AI落子: (%d, %d), 思考时间: %ld秒\n", best_x, best_y, time(NULL) - start_time);
        }
    }
}
// 检查棋盘是否为空
bool is_board_empty() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game.board[i][j] != 0) return false;
        }
    }
    return true;
}