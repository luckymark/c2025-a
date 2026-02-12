#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define MAX_LEVELS 3
#define SCORE_FILE "score.txt"
#define WALL '#'
#define ROLE '@'
#define ROAD ' '
#define BOX '$'
#define TARGET '.'
#define BOX_ON_TARGET '*'
#define ROLE_ON_TARGET '&'
typedef struct Gamestate
{
    char map[MAP_HEIGHT][MAP_WIDTH];
    int role_x,role_y;
    int box_count;
    int box_x[10];
    int box_y[10];
    int target_count;
    int target_y[10];
    int target_x[10];
    int steps;
    int level;
}Gamestate;
void init_game(Gamestate*game){
    int current_level = game->level;
    memset(game, 0, sizeof(Gamestate));
    game->steps = 0;
    game->level = current_level; 
}
bool loadmap(Gamestate*game,const char *filename){
    FILE*file=fopen(filename,"r");
    if(!file){
        return false;
    }
    init_game(game);
    for(int y=0;y<MAP_HEIGHT;y++){
        char line[MAP_WIDTH+2];
        if(fgets(line,sizeof(line),file)==NULL){
            break;
        }
        for(int x=0;x<MAP_WIDTH;x++){
            if(line[x]=='\n'||line[x]=='\0')break;
            game->map[y][x]=line[x];
            if (line[x] == ROLE || line[x] == ROLE_ON_TARGET) {
                game->role_x = x;
                game->role_y = y;
                game->map[y][x] = (line[x] == ROLE) ? ROAD : TARGET;
            }
            if (line[x] == BOX || line[x] == BOX_ON_TARGET) {
                game->box_x[game->box_count] = x;
                game->box_y[game->box_count] = y;
                game->box_count++;
                game->map[y][x] = (line[x] == BOX) ? ROAD : TARGET;
            }
            if (line[x] == TARGET || line[x] == ROLE_ON_TARGET || line[x] == BOX_ON_TARGET) {
                game->target_x[game->target_count] = x;
                game->target_y[game->target_count] = y;
                game->target_count++;
            }
        }

    }
    fclose(file);
    return true;
}

void move_role(Gamestate*game,int dx,int dy){
    int new_x=game->role_x+dx;
    int new_y=game->role_y+dy;
    if(new_x<0||new_x>=MAP_WIDTH||new_y<0||new_y>=MAP_HEIGHT){
        return;
    }
    if(game->map[new_y][new_x]==WALL){
        return;
    }
    bool push_box=false;
    int box_index=-1;
    for (int i = 0; i < game->box_count; i++) {
        if (game->box_x[i] == new_x && game->box_y[i] == new_y) {
            push_box = true;
            box_index = i;
            break;
        }
    }
    if (push_box) {
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        if (box_new_x < 0 || box_new_x >= MAP_WIDTH || 
            box_new_y < 0 || box_new_y >= MAP_HEIGHT ||
            game->map[box_new_y][box_new_x] == WALL) {
            return;
        }
        for (int i = 0; i < game->box_count; i++) {
            if (i != box_index && 
                game->box_x[i] == box_new_x && 
                game->box_y[i] == box_new_y) {
                return;
            }
        }
        game->box_x[box_index] = box_new_x;
        game->box_y[box_index] = box_new_y;
    }
    game->role_x = new_x;
    game->role_y = new_y;
    game->steps++;
}
void save(int level,int steps){
    FILE*file=fopen(SCORE_FILE,"a");
    if(file){
        fprintf(file, "关卡 %d: %d 步\n", level, steps);
        fclose(file);
    }
}

void draw(const Gamestate*game){
    system("clear");
    printf("关卡: %d  步数: %d\n\n", game->level, game->steps);
    char display[MAP_HEIGHT][MAP_WIDTH];
    memcpy(display,game->map,sizeof(display));
    for (int i = 0; i < game->target_count; i++) {
        int x = game->target_x[i];
        int y = game->target_y[i];
        if (display[y][x] == ROAD) {
            display[y][x] = TARGET;
        }
    }
    for (int i = 0; i < game->box_count; i++) {
        int x = game->box_x[i];
        int y = game->box_y[i];
        display[y][x] = (display[y][x] == TARGET) ? BOX_ON_TARGET : BOX;
    }
    display[game->role_y][game->role_x] = (game->map[game->role_y][game->role_x] == TARGET) ? ROLE_ON_TARGET : ROLE;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("%.*s\n", MAP_WIDTH, display[y]);
    }
    printf("\nWASD移动, R重置, Q退出\n");
}
bool check_win(const Gamestate *game) {
    for (int i = 0; i < game->box_count; i++) {
        bool on_target = false;
        for (int j = 0; j < game->target_count; j++) {
            if (game->box_x[i] == game->target_x[j] && 
                game->box_y[i] == game->target_y[j]) {
                on_target = true;
                break;
            }
        }
        if (!on_target) return false;
    }
    return true;
}


int main(){
    Gamestate game;
    char level_file[MAX_LEVELS][20]={
        "level1.txt", "level2.txt", "level3.txt"
    };
    bool running=true;
    game.level=1;
    while (running && game.level <= MAX_LEVELS) {
        if (!loadmap(&game, level_file[game.level-1])) {
            printf("无法加载关卡 %d\n", game.level);
            break;
        }
        
        bool level_complete = false;
        
        while (!level_complete) {
            draw(&game);
            
            if (check_win(&game)) {
                printf("\n恭喜！你赢了关卡 %d！步数: %d\n", game.level, game.steps);
                save(game.level, game.steps);
                level_complete = true;
                break;
            }
            
            printf("请输入移动方向 (WASD): ");
            char input = getchar();
            while (getchar() != '\n');
            
            switch (input) {
                case 'w': case 'W': move_role(&game, 0, -1); break;
                case 'a': case 'A': move_role(&game, -1, 0); break;
                case 's': case 'S': move_role(&game, 0, 1); break;
                case 'd': case 'D': move_role(&game, 1, 0); break;
                case 'r': case 'R': level_complete = true; break;
                case 'q': case 'Q': running = false; level_complete = true; break;
                default: break;
            }
        }
        
        if (running && level_complete) {
            printf("\n按任意键继续下一关...\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            getchar();
            game.level++;
        }
    }
    return 0;
}