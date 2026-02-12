#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 11
int maze[SIZE][SIZE];
int x,y,endx,endy;

void generateMaze(int x1,int y1){
    if(x1==SIZE-2&&y1==SIZE-2)return;
    int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
    int order[4]={0,1,2,3};
    for(int i=3;i>0;--i){
        int j=rand()%(i+1);
        int t=order[i];order[i]=order[j];order[j]=t;
    }
    for(int i=0;i<4;++i){
        int nx=x1+2*dir[order[i]][0];
        int ny=y1+2*dir[order[i]][1];
        if(nx>=1&&nx<=SIZE-2&&ny>=1&&ny<=SIZE-2&&maze[nx][ny]==0){
            maze[x1+dir[order[i]][0]][y1+dir[order[i]][1]]=1;
            maze[nx][ny]=1;
            generateMaze(nx,ny);
        }
    }
}

void init_maze(){
    srand((unsigned)time(NULL));
    for(int i=0;i<SIZE;++i)for(int j=0;j<SIZE;++j)maze[i][j]=0;
    maze[1][1]=1;
    maze[SIZE-2][SIZE-2]=1;
    generateMaze(1,1);
    if(maze[SIZE-3][SIZE-2]==0) maze[SIZE-3][SIZE-2]=1;
    if(maze[SIZE-2][SIZE-3]==0) maze[SIZE-2][SIZE-3]=1;
    x=1;y=1;endx=SIZE-2;endy=SIZE-2;
}
void move_role(char c){
    int dx=0,dy=0;
    if(c=='w'||c=='W')dx=-1;
    else if(c=='s'||c=='S')dx=1;
    else if(c=='a'||c=='A')dy=-1;
    else if(c=='d'||c=='D')dy=1;
    else return;
    int nx=x+dx,ny=y+dy;
    if(nx<0||nx>=SIZE||ny<0||ny>=SIZE)return;
    if(maze[nx][ny]==1){x=nx;y=ny;}
}

void draw(){
    system("clear");
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if(i==x&&j==y)printf("@");
            else if(i==endx&&j==endy)printf("E");
            else printf("%c",maze[i][j]?' ':'#');
        }
        printf("\n");
    }
}

int main(){
    init_maze();
    while(1){
        draw();
        if(x==endx&&y==endy){printf("恭喜你走出迷宫！\n");break;}
        char c=getchar();
        if(c=='q'||c=='Q')break;
        move_role(c);
        while(getchar()!='\n');
    }
    return 0;
}