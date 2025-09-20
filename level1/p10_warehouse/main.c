#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
FILE*file_inventory;
bool whether_open_inventory(FILE*file,int type);
void whether_initialization_inventory();
void inventory_initialization();
void print_inventory();
void in_inventory(int cargo,int number);
void out_inventory(int cargo,int number);
void choose_function(char choose);
void close_inventory();
void showTIME();
bool whether_open_inventory(FILE*file,int type){
    if(!file){
        switch(type){
            case 0:printf("Fail to intializate inventory\n");       break;
            case 2:printf("Fail to read the inventory\n");          break;
            case 3:printf("Fail to rewrite the inventory.txt\n");   break;
        }
        return true;
    }
    return false;
}
void whether_initialization_inventory(){
    file_inventory=fopen("inventory.txt","r");
    if(!file_inventory){
        inventory_initialization();
        return ;
    }
    char a[100];
    fgets(a,sizeof(a),file_inventory);
    if(a==NULL){
        fclose(file_inventory);
        inventory_initialization();
    }
}
void inventory_initialization(){
    file_inventory=fopen("inventory.txt","w");
    if(whether_open_inventory(file_inventory,0)){
        return ;
    }
    for(int i=1;i<=9;i++){
        fprintf(file_inventory,"0\n");
    }
    fclose(file_inventory);
}
void print_inventory(){
    file_inventory=fopen("inventory.txt","r");
    if(whether_open_inventory(file_inventory,2)){
        return ;
    }
    char temp[200];
    int line=1;
    while(fgets(temp,sizeof(temp),file_inventory)!=NULL){
        printf("size_%d:%s",line,temp);
        line++;
    }
    fclose(file_inventory);
}
void in_inventory(int cargo,int number){
    file_inventory=fopen("inventory.txt","r");
    if(whether_open_inventory(file_inventory,2)){
        return ;
    }
    char temp_inventory[9][10];
    int line=0;
    while(fgets(temp_inventory[line],sizeof(temp_inventory[line]),file_inventory)&&line<9){
        temp_inventory[line][strcspn(temp_inventory[line],"\n")]='\0';
        line++;
    }
    fclose(file_inventory);
    int new_number=number+atoi(temp_inventory[cargo-1]);
    sprintf(temp_inventory[cargo-1],"%d",new_number);
    file_inventory=fopen("inventory.txt","w");
    if(whether_open_inventory(file_inventory,3)){
        return ;
    }
    for(int i=0;i<9;i++){
        fprintf(file_inventory,"%s\n",temp_inventory[i]);
    }
    fclose(file_inventory);
}
void out_inventory(int cargo,int number){
    file_inventory=fopen("inventory.txt","r");
    if(whether_open_inventory(file_inventory,2)){
        return ;
    }
    char temp_inventory[9][10];
    int line=0;
    while(fgets(temp_inventory[line],sizeof(temp_inventory[line]),file_inventory)&&line<9){
        temp_inventory[line][strcspn(temp_inventory[line],"\n")]='\0';
        line++;
    }
    fclose(file_inventory);
    int new_number=atoi(temp_inventory[cargo-1])-number;
    if(new_number<0){
        printf("The number you fetch out from inventory more than its number in the inventory\n");
        Sleep(2000);
        return ;
    }
    sprintf(temp_inventory[cargo-1],"%d",new_number);
    file_inventory=fopen("inventory.txt","w");
    if(whether_open_inventory(file_inventory,3)){
        Sleep(2000);
        return;
    }
    for(int i=0;i<9;i++){
        fprintf(file_inventory,"%s\n",temp_inventory[i]);
    }
    fclose(file_inventory);
}
void choose_function(char choose){
    printf("please push the pointed number to function your invrntory:\n'1'->print the inventory\n'2'->input cargo\n'3'->output cargo\n'4'->close the inventory\n");
    int cargo,number;
    switch(choose){
        case '1':
            system("cls");
            print_inventory();
            break;
        case '2':
            system("cls");
            printf("Please scanf the size of the cargo and the number of it you want to put into the inventory\n");
            scanf("%d%d",&cargo,&number);
            in_inventory(cargo,number);
            break;
        case '3':
            system("cls");
            printf("Please scanf the size of the cargo and the number of it you want to fetch out from the inventory\n");
            scanf("%d%d",&cargo,&number);
            out_inventory(cargo,number);
            break;
        case '4':
            system("cls");
            break;
        default:
            system("cls");
            choose_function(getch());
    }
}
void close_inventory(){
    MessageBox(0,TEXT("OK"),TEXT("The inventory is been closed"),MB_OK);
    _Exit(0);
}
void showTIME(){
    whether_initialization_inventory();
    while(1){
        printf("please push the pointed number to function your invrntory:\n'1'->print the inventory\n'2'->input cargo\n'3'->output cargo\n'4'->close the inventory\n");
        choose_function(getch());
    }
}
int main(){
    showTIME();
    return 0;
}
