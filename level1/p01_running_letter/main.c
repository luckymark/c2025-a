#include "unistd.h"
#include"stdio.h"
#define WIDE_CONSOLE 151
void clear_line(int i){
    printf("\r");
    for(int j=0;j<i;j++){
        printf(" ");
    }
    printf("\r");
    fflush(stdout);
}
void print_letters(int position){
    for(int i=0;i<position;i++){
        printf(" ");
    }
    printf("f");
    fflush(stdout);
}
int main(){
    int position=0;
    int direction=1;
    while(1){
            clear_line(WIDE_CONSOLE);
            if(position>=0&&position<WIDE_CONSOLE){
                print_letters(position);
                position+=direction;
            }
            else{
                direction=-direction;
                position+=direction*2;//meke letter more fluent
                print_letters(position);
            }
        
        usleep(15000);
    }
    return 0;
}