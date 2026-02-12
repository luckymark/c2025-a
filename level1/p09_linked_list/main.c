#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next; 
} Node;

typedef struct linked_list {  
    Node* head;
    Node* tail;
    Node* current;  
} LinkedList;


Node* create_node(int data) { 
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
    return p;
}

void insert_front(LinkedList* list, int value) {
    Node* p = create_node(value);
    p->next = list->head;
    list->head = p;
    
    if (list->tail == NULL) {  
        list->tail = p;
    }
}

void insert_tail(LinkedList* list, int value) {
    Node* p = create_node(value);
    
    if (list->tail == NULL) { 
        list->head = list->tail = p;
    } else {
        list->tail->next = p;
        list->tail = p;
    }
}

void print_linked_list(LinkedList* list) {
    list->current = list->head;
    while (list->current != NULL) {
        printf("%d ", list->current->data);
        list->current = list->current->next;
    }
    printf("\n");
}

int foundData(LinkedList* list, int data) {
    static int n = 1; 
    if (list->current == NULL) {
        n = 1;  
        list->current = list->head;  
        return -1;
    }
    while (list->current != NULL) {
        if (list->current->data == data) {
            int result = n;
            n++;
            list->current = list->current->next;
            return result;
        }
        n++;
        list->current = list->current->next;
    }
    n = 1; 
    return -1;
}

void reverse_linked_list(LinkedList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    
    list->tail = list->head;  
    list->current = list->head;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    list->head = prev; 
}

void free_linked_list(LinkedList* list) {
    Node* current = list->head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = list->tail = NULL;  
}

int main() {
    LinkedList list = {NULL, NULL, NULL}; 
    
    for (int i = 1; i < 10; i++) {
        insert_tail(&list, i);
    }
    print_linked_list(&list);
    
    insert_tail(&list, 5);
    insert_tail(&list, 6);
    insert_tail(&list, 5);
    
    
    (&list)->current = (&list)->head; 
    int n = foundData(&list, 5);
    while (n != -1) {
        printf("5的位置：%d\n", n);
        n = foundData(&list, 5);
    }
    
    reverse_linked_list(&list);
    print_linked_list(&list);
    
    free_linked_list(&list); 
    
    return 0;
}