#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct Sllist{
    int data;
    bool beFound;
    struct Sllist*point;
}Sllist;
Sllist*create_singly_linked_list(Sllist*head_node){
    head_node=(Sllist*)malloc(sizeof(Sllist));
    head_node->point=NULL;
    return head_node;
}
Sllist*create_new_node(int data){
    Sllist*new_node=(Sllist*)malloc(sizeof(Sllist));
    new_node->data=data;
    new_node->beFound=true;
    return new_node;
}
void insert(Sllist*head_node,int data){
    Sllist*new_node=create_new_node(data);
    new_node->point=head_node->point;
    head_node->point=new_node;
}
void delete(Sllist*head_node,int data){
    if(head_node->point==NULL){
        printf("This singly linked list is empty\n");
        return ;
    }
    Sllist*now_node=head_node->point;
    Sllist*now_front_node=head_node;
    while(now_node->data!=data){
        if(now_node->point==NULL){
            printf("This data is not exist in this singly linked list\n");
            return ;
        }
        now_front_node=now_node;
        now_node=now_node->point;
    }
    now_front_node->point=now_node->point;
    free(now_node);
}
void print_singly_linked_list(Sllist*head_node){
    if(head_node->point==NULL){
        printf("This singly linked list is empty\n");
        return ;
    }
    Sllist*now_node=head_node->point;
    while(now_node->point){
        printf("%d\t",now_node->data);
        now_node=now_node->point;
    }
    printf("%d\n",now_node->data);
}
Sllist*create_reverse_singly_linked_list(Sllist*last_node){
    last_node=(Sllist*)malloc(sizeof(Sllist));
    last_node->point=NULL;
    return last_node;
}
void reverse(Sllist*head_node,Sllist*last_node){
    Sllist*new_node=head_node->point;
    while(new_node->point!=NULL){
        insert(last_node,new_node->data);
        new_node=new_node->point;
    }
    insert(last_node,new_node->data);
}
int find_data(Sllist*head_node,int data){
    int sumOfNode=1;
    Sllist*now_node=head_node->point;
    while(now_node->point!=NULL){
        if(now_node->data==data&&now_node->beFound){
            now_node->beFound=false;
            return sumOfNode;
        }
        sumOfNode++;
        now_node=now_node->point;
    }
    if(now_node->data==data&&now_node->beFound){
        now_node->beFound=false;
        return sumOfNode;
    }
    return -1;
}
int main(){
    Sllist*head_node=create_singly_linked_list(head_node);
    insert(head_node,1);
    insert(head_node,2);
    insert(head_node,5);
    insert(head_node,5);
    print_singly_linked_list(head_node);
    delete(head_node,2);
    print_singly_linked_list(head_node);
    Sllist*last_node=create_reverse_singly_linked_list(last_node);
    reverse(head_node,last_node);
    print_singly_linked_list(last_node);
    printf("The '5'is at the %d node\n",find_data(last_node,5));
    printf("The '5'is at the %d node\n",find_data(last_node,5));
    printf("The '5'is at the %d node\n",find_data(last_node,5));
    return 0;
}
