#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_LIST 100
#define FILELIST "ku.dat"
typedef struct wupingList{
    char model[50];
    int quantity;
}wupingList;
wupingList List[MAX_LIST];
int count=0; 
void displayList() {
    printf("\n=== 存货列表 ===\n");
    printf("%-20s %-10s\n", "型号", "数量");
    printf("-------------------- ----------\n");
    
    for (int i = 0; i <count; i++) {
        printf("%-20s %-10d\n", List[i].model, List[i].quantity);
    }
    
    printf("\n");
}
void saveList(){
    FILE *file=fopen(FILELIST,"wb");
    if(file==NULL){
        printf("文件不存在");
        return;
    }
    fwrite(&count,sizeof(int),1,file);
    fwrite(List,sizeof(wupingList),count,file);
    fclose(file);
}

void loadList(){
    FILE *file=fopen(FILELIST,"rb");
    if(file==NULL){
        printf("文件不存在");
        return;
    }
    fread(&count,sizeof(int),1,file);
    fread(List,sizeof(wupingList),count,file);
    fclose(file);
}
void pushList(){
    char model[100];
    int quantity;
    printf("请输入型号\n");
    scanf("%s",model);
    printf("请输入入库数量\n");
    scanf("%d",&quantity);
    for(int i=0;i<count;i++)
    {
        if(strcmp(List[i].model,model)==0){
            List->quantity+=quantity;
            printf("完成入库");
            return;
        }
    }
    if(count<MAX_LIST){
        strcpy(List[count].model,model);
        List[count].quantity+=quantity;
        count++;
        printf("已经存入\n");
    }
    else{
        printf("已满，无法操作\n");
    }
}
void popList(){
    char model[100];
    int quantity;
    printf("请输入货物型号\n");
    scanf("%s",model);
    printf("请输入出库数量");
    scanf("%d",&quantity);
    for(int i=0;i<count;i++){
        if(strcmp(List[i].model,model)==0){
            if(List[i].quantity>=quantity){
                List[i].quantity-=quantity;
                printf("完成出库，%s还剩%d\n",model,List[i].quantity);
            }
            if(List[i].quantity==0){
                for(int j=i;j<count-1;j++){
                    List[j]=List[j+1];
                }
                count--;
            }
            else{
                printf("库存不足，库存中仅有%d",List[i].quantity);
            }
            return;
        }
    }
    printf("未存入此货物");
}
void initMenu(){
    const char *menu[6]={
        "---进销存系统---",
        "1.显示存货列表  ",
        "2.入库         ",
        "3.出库         ",
        "4.退出程序     ",
        "请选择操作     "
    };
    for(int i=0;i<6;i++){
        printf("%s\n",menu[i]);
    }
    int choice=0;
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        system("clear");
        loadList();
        displayList();
        usleep(50000);
        initMenu();
        break;
    case 2:
        system("clear");
        pushList();
        usleep(50000);
        initMenu();
        break;
    case 3:
        system("clear");
        popList();
        usleep(50000);
        initMenu();
        break;
    case 4:
        system("clear");
        saveList();
        return;
        break;
    default:
        printf("无效输入重新输入");
        usleep(50000);
        system("clear");
        initMenu();
    }

}
int main() {
    initMenu();
    return 0;
}