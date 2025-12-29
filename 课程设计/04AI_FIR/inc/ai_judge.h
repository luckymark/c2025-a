
#ifndef __AI_JUDAGE_H
#define __AI_JUDAGE_H

#include "display.h"

#ifdef __cplusplus
exteern "C" {
#endif

    bool is_board_empty();
    int overall_evaluate() ;
    int check_threat(int player) ;
    int evaluate_direction(int x, int y, int dx, int dy, int player) ;

    void get_quality_moves(int moves[][2], int* move_count, int player) ;

    int alpha_beta_search(int depth, int alpha, int beta, int player, time_t start_time);

    void ai_move();

#ifdef __cplusplus
}
#endif

#endif /* __BLUETOOTH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
