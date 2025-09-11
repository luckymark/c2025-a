#include<stdio.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
//0为闭路 1为迷宫路线生成点 2为开路 3为人物 4为终点 
//全局变量
int mate[21][21];
int current_Line=1,current_Column=1;
//函数原型
void move_1(char keyboard,int current_line,int current_column);
void move(char keyboard,int current_line,int current_column);//未完成
void mate_intialization();
void mate_intialization_2();
void mate_maker_routeplan(int random_direction,int current_line,int current_column);
void mate_maker(int current_line,int current_column);
void print_mate_2(int line,int column);
void print_mate();
void gametime();
//函数
void move_1(char keyboard,int current_line,int current_column){
    keyboard=getch();
    move(keyboard,current_line,current_column);
}
void move(char keyboard,int current_line,int current_column){
    switch(keyboard){
        case 'a':
            if(mate[current_line][current_column-1]==2||mate[current_line][current_column-1]==4){
                mate[current_line][current_column]=mate[current_Line][current_column-1];
                mate[current_Line][current_column-1]=3;
                current_Column=current_column-1;
            }else{
                move_1(keyboard,current_line,current_column);
            }
            break;
        case 's':
            if(mate[current_line+1][current_column]==2||mate[current_line+1][current_column]==4){
                mate[current_line][current_column]=mate[current_Line+1][current_column];
                mate[current_Line+1][current_column]=3;
                current_Line=current_line+1;
            }else{
                move_1(keyboard,current_line,current_column);
            }
            break;
        case 'd':
            if(mate[current_line][current_column+1]==2||mate[current_line][current_column+1]==4){
                mate[current_line][current_column]=mate[current_Line][current_column+1];
                mate[current_Line][current_column+1]=3;
                current_Column=current_column+1;
            }else{
                move_1(keyboard,current_line,current_column);
            }
            break;
        case 'w':
            if(mate[current_line-1][current_column]==2||mate[current_line-1][current_column]==4){
                mate[current_line][current_column]=mate[current_Line-1][current_column];
                mate[current_Line-1][current_column]=3;
                current_Line=current_line-1;
            }else{
                move_1(keyboard,current_line,current_column);
            }
            break;
        default :
            move_1(keyboard,current_line,current_column);
    }
}
void mate_intialization(){
    for(int i=0;i<21;i++){
        for(int j=0;j<21;j++){
            if(i%2==1&&j%2==1){
                mate[i][j]=1;
            }else{
                mate[i][j]=0;
            }
        }
    }
    mate[1][1]=2;//简单化处理：令【1】【1】为迷宫入口
}
void mate_intialization_2(){//生成终点
    mate[19][19]=4;
    mate[1][1]=3;
}
void mate_maker_routeplan(int random_direction,int current_line,int current_column){
    switch(random_direction){
        case 0://下
            if(current_line<=17){
                if(mate[current_line+2][current_column]==1){
                    mate[current_line+2][current_column]=2,mate[current_line+1][current_column]=2;
                    mate_maker(current_line+2,current_column);
                    return ;
                }else{
                    return ;
                }
            }else{
                return ;
            }
            break;
        case 1://右
            if(current_column<=17){
                if(mate[current_line][current_column+2]==1){
                    mate[current_line][current_column+2]=2,mate[current_line][current_column+1]=2;
                    mate_maker(current_line,current_column+2);
                    return ;
                }else{
                    return ;
                }
            }else{
                return ;
            }
            break;
        case 2://上
            if(current_line>=3){
                if(mate[current_line-2][current_column]==1){
                    mate[current_line-2][current_column]=2,mate[current_line-1][current_column]=2;
                    mate_maker(current_line-2,current_column);
                    return ;
                }else{
                    return ;
                }
            }else{
                return ;
            }
            break;
        case 3://左
            if(current_column>=3){
                if(mate[current_line][current_column-2]==1){
                    mate[current_line][current_column-2]=2,mate[current_line][current_column-1]=2;
                    mate_maker(current_line,current_column-2);
                    return ;
                }else{
                    return ;
                }
            }
            else{
                return ;
            }
            break;
    }
}
void mate_maker(int current_line,int current_column){
    while(1){
        int random_direction=rand()%4;
        if((mate[current_line-2][current_column]==1||mate[current_line+2][current_column]==1||mate[current_line][current_column+2]==1||mate[current_line][current_column-2]==1)==0){
            return ;
        }else{
            mate_maker_routeplan(random_direction,current_line,current_column);
        }
    }
}
void print_mate_2(int line,int column){
    switch(mate[line][column]){
        case 0:
            printf("\033[1;34m0\033[0m");
            break;
        case 2:
            printf(" ");
            break;
        case 3:
            printf("\033[1;32m3\033[0m");
            break;
        case 4:
            printf("\033[1;31m4\033[0m");
            break;
    }
}
void print_mate(){
    printf("\033[1;31m'0'is the wall\n'3'is the man\n'4'is the target locate\n\033");
    for(int i=0;i<21;i++){
        printf("\t");
        for(int j=0;j<21;j++){
            print_mate_2(i,j);
        }
        printf("\n");
    }
}
void gametime(){
    while(1){
        print_mate();
        move(getch(),current_Line,current_Column);
        system("cls");
        if(mate[19][19]==3){
            MessageBox(0,TEXT("Congrutulations!"),TEXT("Gameover"),NULL);
            break;
        }
    }
}
int main(){
    srand((unsigned)time(NULL));
    mate_intialization();
    mate_maker(1,1);
    mate_intialization_2();
    gametime();
    return 0;
}
