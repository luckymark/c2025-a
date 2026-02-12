#include <stdio.h>
#include <stdlib.h>
typedef struct letter{
    int*data;
    int front;
    char name[2];
}letter;
int creatletter(letter**La,char name){
    *La=(letter*)malloc(sizeof(letter));
    if(!*La) return 0;
    (*La)->data=(int*)malloc(64*sizeof(int));
    if(!(*La)->data){
        free(*La);
        return 0;
    }
    (*La)->front=-1;
    (*La)->name[0]=name;
    (*La)->name[1]='\0';
    return 1;
}
void destroyLetter(letter*La)
{
    if (La) {
        free(La->data);
        free(La);
    }
}
void initLetter(letter*La){
    for(int i=0;i<64;i++){
        La->data[i]=i+1;
    }
}
void push(letter*La,int data){
    La->front++;
    La->data[La->front]=data;
}
int pop(letter*La){
    int x=La->data[La->front];
    La->front--;
    return x;
}
void action(letter*La,letter*Lc,letter*Lb,int n){
    if (n == 1) {
        push(Lb,pop(La));
        printf("Move disk  from %s to %s\n",La->name,Lb->name);
        return;
    }
    action(La,Lb,Lc,n-1);
    push(Lb,pop(La));
    printf("Move disk  from %s to %s\n",La->name,Lb->name);
    action(Lc,La,Lb,n-1);
}
int main() {
    letter*La;
    letter*Lb;
    letter*Lc;
    creatletter(&La,'A');
    initLetter(La);
    creatletter(&Lb,'B');
    creatletter(&Lc,'C');
    action(La,Lc,Lb,3);
    destroyLetter(La);
    destroyLetter(Lb);
    destroyLetter(Lc);
    return 0;
}
