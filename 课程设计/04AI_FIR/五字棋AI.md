# 五子棋游戏实验报告

##### 学院：计算机科学与工程学院

##### 专业：计算机类

##### 班级：05班

##### 姓名：夏凡程

##### 学号：2025080905020

##### 指导教师：俸志刚

## 1. 实验概述

### 1.1 实验目的
- 学习如何独立于操作系统的图形界面，来绘制图形和渲染文本，从而创建出简单五子棋游戏
- 学习Alpha-Beta剪枝算法在棋类游戏中的实现
- 启发式评估函数的设计与优化

## 2. 系统需求分析

### 2.1 功能需求

**2.1.1 图形显示模块 (display.c)**

- **棋盘绘制**: 实现标准15×15网格棋盘
- **棋子渲染**: 黑白棋
- **状态面板**: 实时显示游戏状态、当前回合、操作说明
- **中文本地化**: 自动检测系统中文字体，支持中文界面
- **用户交互**: 鼠标点击落子，键盘快捷键操作

**2.1.2 AI决策模块 (ai_judge.c)**

- **棋局评估**: 实时评估棋句情况，进而实现简单AI
- **威胁检测**: 实时识别必胜点和关键防守点
- **智能搜索**: 实现深度2-6层的Alpha-Beta剪枝算法
- **移动优化**: 质量移动生成算法减少搜索空间
- **时间控制**: 迭代加深搜索

**2.1.3 数据存储模块 (input_storage.c)**

- **游戏存档**: 保存完整游戏状态
- **进度加载**: 从存档文件恢复游戏

**2.1.4 主控模块 (main.c)**

- **游戏流程**: 控制游戏初始化、进行、结束全流程
- **事件处理**: 响应键盘鼠标事件
- **AI调度**: 控制AI思考时机和落子逻辑

## 3. 实现

### 3.1 核心数据结构设计

#### 3.1.1游戏状态结构体

```c
typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];  // 棋盘状态矩阵
    int turn;                           // 当前玩家(1:黑棋,2:白棋)
    bool game_over;                     // 游戏结束标志
    int winner;                         // 获胜方标识
} GameStatues;

extern GameStatues game;  // 全局游戏状态实例
```

#### 3.1.2棋型评分体系

```c
typedef struct {
    int five;           // 五连: 1000000
    int live_four;      // 活四: 100000
    int sleep_four;     // 眠四: 10000
    int live_three;     // 活三: 10000
    int sleep_three;    // 眠三: 1000
    int live_two;       // 活二: 1000
    int sleep_two;      // 眠二: 100
} PatternScore;

PatternScore score_table = {
    .five = 1000000, .live_four = 100000, .sleep_four = 10000,
    .live_three = 10000, .sleep_three = 1000, .live_two = 1000, .sleep_two = 100
};
```

### 3.2 关键算法实现

#### 3.2.1 Alpha-Beta剪枝搜索算法

##### 搜索算法核心*[常规算法框架]*

```c
int alpha_beta_search(int depth, int alpha, int beta, int player, time_t start_time) {
    // 终止条件: 达到深度限制或游戏结束
    if (depth == 0 || game.game_over) 
        return professional_evaluate();
  
    // 时间控制: 单步搜索不超过5秒
    if (time(NULL) - start_time > 5) 
        return professional_evaluate();
  
    int moves[BOARD_SIZE * BOARD_SIZE][2];
    int move_count;
    get_quality_moves(moves, &move_count, player);
  
    // Max玩家(黑棋)搜索逻辑
    if (player == 1) {
        int max_eval = -10000000;
        for (int i = 0; i < move_count; i++) {
            int x = moves[i][0], y = moves[i][1];
            game.board[x][y] = player;  
            int eval = alpha_beta_search(depth-1, alpha, beta, 3-player, start_time);
            game.board[x][y] = 0;       
          
            if (eval > max_eval) max_eval = eval;
            if (eval > alpha) alpha = eval;
            if (beta <= alpha) break;   // Beta剪枝
        }
        return max_eval;
    } 
    // Min玩家(白棋)搜索逻辑
    else {
        // 对称实现...
    }
}
```

#### 3.2.2 棋型评估函数

##### 方向性评估

```c
int evaluate_direction(int x, int y, int dx, int dy, int player) {
    int count = 1, block = 0, empty = 0;
  
    // 正向扫描
    for (int k = 1; k <= 4; k++) {
        int nx = x + k * dx, ny = y + k * dy;
        if (!in_board(nx, ny)) { block++; break; }
        if (game.board[nx][ny] == player) count++;
        else if (game.board[nx][ny] == 0) { empty++; break; }
        else { block++; break; }
    }
  
    // 反向扫描
    for (int k = 1; k <= 4; k++) {
        int nx = x - k * dx, ny = y - k * dy;
        if (!in_board(nx, ny)) { block++; break; }
        if (game.board[nx][ny] == player) count++;
        else if (game.board[nx][ny] == 0) { empty++; break; }
        else { block++; break; }
    }
  
    // 棋型评分逻辑
    if (count >= 5) return score_table.five;
    if (block == 2) return 0;
  
    switch (count) {
        case 4: return block == 0 ? score_table.live_four : score_table.sleep_four;
        case 3: return block == 0 ? score_table.live_three : score_table.sleep_three;
        case 2: return block == 0 ? score_table.live_two : score_table.sleep_two;
        case 1: return block == 0 ? score_table.sleep_two / 10 : 0;
        default: return 0;
    }
}
```

#### 3.2.3 智能移动生成算法

##### 质量移动生成*[减少搜索时间，提高搜索效率]*

```c
void get_quality_moves(int moves[][2], int* move_count, int player) {
    *move_count = 0;
    int priority_count = 0, normal_count = 0;
    int priority_moves[BOARD_SIZE*BOARD_SIZE][2];
    int normal_moves[BOARD_SIZE*BOARD_SIZE][2];
  
    // 第一阶段: 检查威胁位置
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game.board[i][j] != 0) continue;
          
            // 检查进攻威胁(形成五连)
            game.board[i][j] = player;
            if (check_win(i, j, player)) {
                priority_moves[priority_count][0] = i;
                priority_moves[priority_count][1] = j;
                priority_count++;
            }
            game.board[i][j] = 0;
          
            // 检查防守威胁(阻止对方五连)
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
  
    // 第二阶段: 生成启发式移动(棋子周围3格内)
    if (priority_count == 0) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (game.board[i][j] == 0) continue;
              
                for (int dx = -3; dx <= 3; dx++) {
                    for (int dy = -3; dy <= 3; dy++) {
                        int ni = i + dx, nj = j + dy;
                        if (!in_board(ni, nj) || game.board[ni][nj] != 0) continue;
                      
                        // 去重检查
                        if (!move_exists(normal_moves, normal_count, ni, nj)) {
                            normal_moves[normal_count][0] = ni;
                            normal_moves[normal_count][1] = nj;
                            normal_count++;
                        }
                    }
                }
            }
        }
    }
  
    // 合并移动列表
    merge_moves(moves, move_count, priority_moves, priority_count, 
                normal_moves, normal_count);
  
    // 默认移动: 棋盘中心
    if (*move_count == 0) {
        moves[0][0] = BOARD_SIZE / 2;
        moves[0][1] = BOARD_SIZE / 2;
        *move_count = 1;
    }
}
```

### 3.3 用户界面实现

#### 3.3.1加载中文

```c
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
```

#### 3.3.2图形界面主循环

```c
void draw_board_process(SDL_Renderer* renderer, TTF_Font* font) {
    // 清屏
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
  
    // 分层绘制
    draw_board(renderer);           // 绘制棋盘网格
    draw_stones(renderer);          // 绘制棋子
    draw_status_panel(renderer, font); // 绘制状态面板
  
    // 刷新显示
    SDL_RenderPresent(renderer);
}
```

#### 3.3.3处理鼠标

```c
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
                game.turn = 3 - game.turn;   // 1↔2 最简洁

            }
        }
    }
}
```

#### 3.3.4加载以及保存数据

```c
	fprintf(fp, "%d %d %d\n", game.turn ? 1 : 0, 			game.game_over ? 1 : 0, game.winner);

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x)
            fprintf(fp, "%d ", game.board[x][y]);
        fputc('\n', fp);
    }

    if (fscanf(fp, "%d %d %d\n", &b, &g, &w) != 3)
```

## 4. 系统测试与分析

### 4.1 测试结果分析

#### 4.1.1 功能测试结果
| 测试类别       | 测试项   | 结果 | 说明               |
| -------------- | -------- | ---- | ------------------ |
| **界面功能**   | 棋盘绘制 | ✅    | 15×15网格正确显示  |
|                | 棋子渲染 | ✅    | 黑白棋子区分明显   |
|                | 状态显示 | ✅    | 实时更新游戏信息   |
| **游戏逻辑**   | 落子规则 | ✅    | 交替落子，禁止重复 |
|                | 胜负判定 | ✅    | 五连珠正确识别     |
|                | 游戏重置 | ✅    | 状态完整重置       |
| **AI智能**     | 基础走法 | ✅    | 符合五子棋基本策略 |
|                | 进攻能力 | ✅    | 能主动形成连珠     |
|                | 防守能力 | ✅    | 能阻止玩家连珠     |
| **数据持久化** | 游戏存档 | ✅    | 完整保存游戏状态   |
|                | 进度加载 | ✅    | 正确恢复游戏       |

### 4.2 测试用例示例

#### 4.2.1胜负判定测试用例

```c
// 测试水平五连识别
void test_horizontal_win() {
    reset_game();
    // 布置测试棋局
    for (int i = 0; i < 5; i++) {
        game.board[5+i][7] = 1;  // 黑棋水平五连
    }
    assert(check_win(5, 7, 1) == true);  // 应识别获胜
}
```

## 5. 系统评估与优化建议

### 5.1 系统优势分析

1. **算法效率优化**
   - Alpha-Beta剪枝有效减少搜索空间
   - 质量移动生成大幅提升搜索效率
   - 迭代加深平衡深度与时间开销

### 5.2 现存问题分析

#### 5.2.1 算法局限性
- **评估函数简单**: 仅考虑局部棋型，缺乏全局形势判断，与网上的五指棋游戏对战会导致陷入***“人机化”***
- **搜索深度有限**: 6层搜索难以应对复杂中盘局面
- **模式识别不足**: 对特殊棋型(如双三、冲四)处理不够完善，以及对于***“空位的利用”***不在识别范围内

#### 5.2.2 功能完整性
- **缺少高级功能**: 无悔棋、提示、棋谱记录等功能
- **难度不可调**: AI强度固定，无法适应不同水平玩家
- **交互体验待提升**: 缺少动画效果和音效反馈

### 5.3 优化改进方案

#### 5.3.1 算法优化路线
1. **评估函数增强**
   
   ```c
   //例如可以加深估值程序
   int advanced_evaluate() {
       int score = professional_evaluate();  // 原有局部评估
       score += evaluate_global_position();  // 全局形势评估
       score += evaluate_mobility();         // 行动力评估
       score += evaluate_threat_patterns();  // 威胁模式评估
       return score;
   }
   ```
   
2. **搜索算法改进**
   
   - 添加开局库减少开局搜索时间
   - 引入历史启发排序提升剪枝效果*[目前还不会]*
   - 可以采取多线程模式提升搜索速度

## 6. 实验总结与展望

### 6.1 实验成果总结

通过本实验，成功实现了一个具备基本智能的五子棋游戏系统，主要成果包括：

1. **完整游戏框架**: 实现了从界面到AI的完整游戏系统
2. **智能决策引擎**: 基于Alpha-Beta剪枝的AI具备中级棋力
3. **良好用户体验**: 直观的图形界面和流畅的操作体验
4. **模块化设计**: 清晰的架构为后续扩展奠定基础

### 6.2 知识收获

1. **算法实践能力**: 深入理解博弈树搜索算法实际应用
2. **系统设计能力**: 掌握中等规模软件系统的架构设计
3. **工程实现经验**: 积累了图形界面开发和调试经验
4. **问题解决能力**: 在调试优化过程中提升技术问题解决能力

**附录A: 完整源代码结构**

- `ai_judge.c/h` - AI决策算法实现
- `display.c/h` - 图形界面和游戏逻辑
- `input_storage.c/h` - 数据持久化功能
- `main.c` - 程序入口和主控逻辑

**附录B: 第三方库依赖**

- SDL2: 图形界面库
- SDL2_ttf: 字体渲染库
- 数学库: 三角函数计算

  
