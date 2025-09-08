#include<stdio.h>
#include<Windows.h>
int GetConsole_HideCursor(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize=sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole,&csbi);
    CONSOLE_CURSOR_INFO cursorinfo;
    GetConsoleCursorInfo(hConsole,&cursorinfo);
    cursorinfo.bVisible=FALSE;
    SetConsoleCursorInfo(hConsole,&cursorinfo);
    return csbi.srWindow.Right-csbi.srWindow.Left+1;
}
int decide_moveNUMBER(int move_NUMBER,const int CONSOLEWIDTH){
    if((move_NUMBER/CONSOLEWIDTH)%2==0){
        return move_NUMBER%CONSOLEWIDTH;
    }else{
        return CONSOLEWIDTH-move_NUMBER%CONSOLEWIDTH;
    }
}
void moving_letter(int move_NUMBER,char LETTER,const int CONSOLEWIDTH){
    printf("\r");
    for(int i=0;i<move_NUMBER-1;i++){
        printf(" ");
    }
    printf("%s",&LETTER);
   if(move_NUMBER%CONSOLEWIDTH!=0){
        printf(" ");
   }
    fflush(stdout);
    Sleep(20);//Decide the speed of the letter
}
int main(){
    const int WIDTH=GetConsole_HideCursor();
    char letter;
    int move_number=1;
    scanf("%c",&letter);
    while(1){
        moving_letter(decide_moveNUMBER(move_number,WIDTH),letter,WIDTH);
        move_number++;
    }
    return 0;
}
Footer
© 2025 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
