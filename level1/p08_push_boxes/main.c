//0 is wall;1 is man;2 is road;3 is box;4 is target 5 is fillman 6 is the symbol of get one flag
#include<stdio.h>
#include<Windows.h>
FILE *file_1,*file_2,*file_3,*file_move_number,*file_open_history;
void hideUcrsor();
void printMateIntoTxt();
void getmate_1();
void getmate_2();
void getmate_3();
void print_mate();
void move(char move,int current_line,int current_column,int numberOfMate);
void gametime(int current_line,int current_column,int numberOfMate);
void printMoveNumber();
void getHistorical_moveNumber(char whether);
int mate_1[11][11]={
    {0,0,0,0,0,0,0,0,0,0,5},
    {0,2,2,2,2,2,0,2,2,0,5},
    {0,1,0,3,2,2,0,0,0,0,5},
    {0,0,2,2,2,2,2,2,4,0,5},
    {0,0,2,2,2,0,0,0,0,0,5},
    {0,0,0,0,0,0,0,0,0,0,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
};
int mate_2[11][11]={
    {0,0,0,0,0,0,0,0,0,0,5},
    {0,2,2,2,2,2,2,4,4,0,5},
    {0,2,3,2,0,0,0,2,2,0,5},
    {0,1,0,2,2,2,2,2,2,0,5},
    {0,2,2,2,3,0,2,2,2,0,5},
    {0,2,0,2,2,0,0,0,0,0,5},
    {0,0,0,0,0,0,0,0,0,0,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5,5,5,5,5},
};
int mate_3[11][11]={
    {0,0,0,0,0,0,0,0,0,0,0},
    {0,1,2,2,2,0,2,2,2,2,0},
    {0,2,2,3,2,2,2,0,2,2,0},
    {0,2,0,0,2,0,2,0,0,2,0},
    {0,2,2,2,2,4,2,2,3,2,0},
    {0,0,2,0,4,0,4,0,2,0,0},
    {0,2,3,2,2,4,2,2,2,2,0},
    {0,2,0,0,2,0,2,0,0,2,0},
    {0,2,2,0,2,2,2,3,2,2,0},
    {0,2,2,2,2,0,2,2,2,2,0},
    {0,0,0,0,0,0,0,0,0,0,0},
};
char mate[11][11];
int current_Line,current_Column;
int flag;
int moveNUMBER;
void hideCursor(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorinfo;
    GetConsoleCursorInfo(hConsole,&cursorinfo);
    cursorinfo.bVisible=FALSE;
    SetConsoleCursorInfo(hConsole,&cursorinfo);
}
void printMateIntoTxt(){
    hideCursor();
    file_1=fopen("mate_1.txt","w");
    file_2=fopen("mate_2.txt","w");
    file_3=fopen("mate_3.txt","w");
    if(file_1==NULL||file_2==NULL||file_3==NULL){
        printf("fail to print txt");
    }
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            fprintf(file_1,"%d",mate_1[i][j]);
        }
        fprintf(file_1,"\n");
    }
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            fprintf(file_2,"%d",mate_2[i][j]);
        }
        fprintf(file_2,"\n");
    }
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            fprintf(file_3,"%d",mate_3[i][j]);
        }
        fprintf(file_3,"\n");
    }
    fclose(file_1);
    fclose(file_2);
    fclose(file_3);
}
void getmate_1(){
    flag=1,current_Line=2,current_Column=1;;
    file_1=fopen("mate_1.txt","r");
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            char c;
            fscanf(file_1,"%c",&c);
            if(c!='\n'){
                mate[i][j]=c;
            }else{
               j--;
            }
        }
    }
    fclose(file_1);
}
void getmate_2(){
    flag=2,current_Line=3,current_Column=1;
    file_2=fopen("mate_2.txt","r");
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            char c;
            fscanf(file_2,"%c",&c);
            if(c!='\n'){
                mate[i][j]=c;
            }else{
                j--;
            }
        }
    }
    fclose(file_2);
}

void getmate_3(){
    flag=4,current_Line=1,current_Column=1;
    file_3=fopen("mate_3.txt","r");
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            char c;
            fscanf(file_3,"%c",&c);
            if(c!='\n'){
                mate[i][j]=c;
            }else{
                j--;
            }
        }
    }
    fclose(file_3);
}
void print_mate(){
    printf("0 is wall;1 is man;2 is road;3 is box;4 is target;6 is the symbol of get a target\nIf you want to remake,please push'r',and of caurse,asdw is the way to control the man\n");
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            switch(mate[i][j]){
                case '0':printf("\033[1;34m%c\033[0m",mate[i][j]);break;
                case '1':printf("\033[1;32m%c\033[0m",mate[i][j]);break;
                case '4':printf("\033[1;31m%c\033[0m",mate[i][j]);break;
                case '3':printf("\033[1;31m%c\033[0m",mate[i][j]);break;
                case '2':printf(" ");break;
                case '6':printf("\033[1;32m%c\033[0m",mate[i][j]);break;
            }
        }
        printf("\n");
    }
    printf("You have moved %d times\n",moveNUMBER);
}
void move(char Move,int current_line,int current_column,int numberOfMate){
    switch(Move){
        case 'a':
            switch(mate[current_line][current_column-1]){
                case '0'||'4'||'5'||'6': move(getch(),current_line,current_column,numberOfMate);break;
                case '2':mate[current_line][current_column]='2',mate[current_line][current_column-1]='1';current_Column--;moveNUMBER++;break;
                case '3':
                    switch(mate[current_line][current_column-2]){
                        case '2':mate[current_line][current_column]='2',mate[current_line][current_column-1]='1',mate[current_line][current_column-2]='3';current_Column--;moveNUMBER++;break;
                        case '0'||'5'||'6':move(getch(),current_line,current_column,numberOfMate);break;
                        case '4':flag--;mate[current_line][current_column-1]='1',mate[current_line][current_column-2]='6',mate[current_line][current_column]='2';current_Column--;moveNUMBER++;break;
                    }break;
            }break;
        case 's':
            switch(mate[current_line+1][current_column]){
                case '0'||'4'||'5'||'6': move(getch(),current_line,current_column,numberOfMate);break;
                case '2':mate[current_line][current_column]='2',mate[current_line+1][current_column]='1';current_Line++;moveNUMBER++;break;
                case '3':
                    switch(mate[current_line+2][current_column]){
                        case '2':mate[current_line][current_column]='2',mate[current_line+1][current_column]='1',mate[current_line+2][current_column]='3';current_Line++;moveNUMBER++;break;
                        case '0'||'5'||'6':move(getch(),current_line,current_column,numberOfMate);break;
                        case '4':flag--;mate[current_line+1][current_column]='1',mate[current_line+2][current_column]='6',mate[current_line][current_column]='2';current_Line++;moveNUMBER++;break;
                    }break;
            }break;
        case 'd':
            switch(mate[current_line][current_column+1]){
                case '0'||'4'||'5'||'6': move(getch(),current_line,current_column,numberOfMate);break;
                case '2':mate[current_line][current_column]='2',mate[current_line][current_column+1]='1';current_Column++;moveNUMBER++;break;
                case '3':
                    switch(mate[current_line][current_column+2]){
                        case '2':mate[current_line][current_column]='2',mate[current_line][current_column+1]='1',mate[current_line][current_column+2]='3';current_Column++;moveNUMBER++;break;
                        case '0'||'5'||'6':move(getch(),current_line,current_column,numberOfMate);break;
                        case '4':flag--;mate[current_line][current_column+1]='1',mate[current_line][current_column+2]='6',mate[current_line][current_column]='2';current_Column++;moveNUMBER++;break;
                    }break;
            }break;
        case 'w':
            switch(mate[current_line-1][current_column]){
                case '0'||'4'||'5'||'6': move(getch(),current_line,current_column,numberOfMate);break;
                case '2':mate[current_line][current_column]='2',mate[current_line-1][current_column]='1';current_Line--;moveNUMBER++;break;
                case '3':
                    switch(mate[current_line-2][current_column]){
                        case '2':mate[current_line][current_column]='2',mate[current_line-1][current_column]='1',mate[current_line-2][current_column]='3';current_Line--;moveNUMBER++;break;
                        case '0'||'5'||'6':move(getch(),current_line,current_column,numberOfMate);break;
                        case '4':flag--;mate[current_line-1][current_column]='1',mate[current_line-2][current_column]='6',mate[current_line][current_column]='2';current_Line--;moveNUMBER++;break;
                    }break;
            }break;
        case 'r':
            switch(numberOfMate){
                case 1:getmate_1();break;
                case 2:getmate_2();break;
                case 3:getmate_3();break;
            }
            break;
        default :move(getch(),current_line,current_column,numberOfMate);
    }
}
void gametime(int current_line,int current_column,int numberOfMate){
    current_Line=current_line,current_Column=current_column;
    while(flag>0){
        print_mate();
        move(getch(),current_Line,current_Column,numberOfMate);
        system("cls");
    }
}
void printMoveNumber(){
    file_move_number=fopen("moveNUMBER.txt","a");
    if(file_move_number==NULL){
        printf("Fail to print the move number");
    }else{
        fprintf(file_move_number,"move number:%d\n",moveNUMBER);
    }
    fclose(file_move_number);
    printf("If you want to visit the historical game move numbers,please push'h'\n");
}
void getHistorical_moveNumber(char whether){
    if(whether=='h'){
        file_open_history=fopen("moveNUMBER.txt","r");
        char c[200];
        while(fgets(c,sizeof(c),file_open_history)){
            printf("%s",c);
        }
        fclose(file_open_history);
    }
    Sleep(3000);
}
int main(){
    printMateIntoTxt();
    getmate_1(),gametime(2,1,1);
    getmate_2(),gametime(3,1,2);
    getmate_3(),gametime(1,1,3);
    printMoveNumber(),getHistorical_moveNumber(getch());
    MessageBox(0,TEXT("Congratulations!"),TEXT("Gameover"),NULL);
    return 0;
}
