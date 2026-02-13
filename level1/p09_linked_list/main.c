#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *CreateList() {
    return NULL;
}

int insert(struct Node **list, int name) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = name;
    temp->next = *list ;
    *list = temp;
    return 0;
}

void append(struct Node *list, int data) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    while (list->next != NULL) {
        list = list->next;
    }
    list->next = temp;
}

int delete(struct Node **list, int index) {//改成二重指针
    struct Node **change = list;
    struct Node *temp1;
    for (int i = 0; i < index; i++) {
        temp1 = *change;
        if ((*change)->next == NULL) {
            return 1;
        }
        change = &(temp1->next);
    }
    free(*change);
    *change =(*change)->next ;
    return 0;
}

int find(struct Node *list, int data, int start) {
    for (int i=0; list != NULL;list = list->next,i++) {
        if ( i>=start && list->data == data) {
            return i;
        }
    }
    return -1;
}

void display(struct Node *list) {
    for (; list != NULL; list = list -> next) {
        printf("%d ", list -> data);
    }
    printf("\n");
}
int main() {
    struct Node *list = CreateList();
    insert(&list, 4);
    insert(&list, 3);
    insert(&list, 2);
    insert(&list, 1);
    append(list, 5);
    append(list, 6);

    display(list);

    struct Node *newlist = CreateList();
    for (struct Node *index = list;index != NULL; index = index->next) {
        insert(&newlist, index->data);
    }
    display(newlist);

    int x = find(list, 5, 0);
    if (x == -1) {
        printf("can't find!\n");
    }
    else {
        printf("The number is located at %d.\n", x);
    }
    int y = find(list, 5, x+1);
    if (y == -1) {
        printf("can't find!\n");
    }
    else {
        printf("The number is located at %d.\n", y);
    }

    append(list, 5);

    int z = find(list, 5, x+1);
    if (z == -1) {
        printf("can't find!\n");
    }
    else {
        printf("The number is located at %d.\n", z);
    }

    return 0;
}