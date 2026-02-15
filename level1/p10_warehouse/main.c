#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<conio.h>

using namespace std;

struct item{
    string id;
    int num;
};

struct LIST{
    struct node{
        item val;
        node *nxt;
    };
    node *head;
    void insert(string id, int num){
        if(head == nullptr){
            head = new node;
            head->val = (item){id, num};
            head->nxt = nullptr;
            return;
        }
        node *now = head;
        while(now != nullptr){
            if(now->nxt == nullptr){
                node *tmp = new node;
                tmp->val = (item){id, num};
                tmp->nxt = nullptr;
                now->nxt = tmp;
                return;
            }
            now = now->nxt;
        }
    }
    bool del(string id, int sum){
        node *now = head, *lst = nullptr;
        while(now != nullptr){
            if(now->val.id == id){
                if(sum > now->val.num){
                    cout << "Error: Not enough items to delete." << endl;
                    return 0;
                }
                else if(sum == now->val.num){
                    if(lst == nullptr) head = now->nxt;
                    else lst->nxt = now->nxt;
                    free(now);
                    return 1;
                }
                else{
                    now->val.num -= sum;
                    return 1;
                }
            }
            if(lst == nullptr) lst = now;
            now = now->nxt;
        }
        return 1;
    }
    void peek( ){
        node *now = head;
        if(now == nullptr){
            cout << "The list is empty." << endl;
            return;
        }
        while(now != nullptr){
            cout << now->val.id << " " << now->val.num << endl;
            now = now->nxt;
        }
        return;
    }
} lst;

int tot;
void build( ){
    ifstream fin("list.txt");
    if(!fin.is_open()){
        ofstream fout("list.txt");
        fout.close( );
        fin.close( );
        tot = 0;
        return;
    }
    fin >> tot;
    for(int i = 1; i <= tot; i++){
        string id; int num;
        fin >> id >> num;
        lst.insert(id, num);
    }
    fin.close( );
}
void updata( ){
    ofstream fout("list.txt", ios::trunc);
    fout << tot << endl;
    LIST::node *now = lst.head;
    while(now != nullptr){
        fout << now->val.id << " " << now->val.num << endl;
        now = now->nxt;
    }
    fout.close( );
}
void show_list( ){
    system("cls");
    lst.peek( );
    system("pause");
}
void add_item( ){
    system("cls");
    cout << "Please input the id and number of the new item: ";
    string id; int num;
    cin >> id >> num;
    tot++;
    lst.insert(id, num);
    cout << "The item has been added." << endl;
    system("pause");
}
void del_item( ){
    system("cls");
    cout << "Please input the id and the sum of the item you want to remove: ";
    string id; int sum;
    cin >> id >> sum;
    if(lst.del(id, sum)){
        tot--;
        cout << "The item has been removed." << endl;
    }
    system("pause");
}
void menue( ){
    system("cls");
    cout << "1. Show List" << endl;
    cout << "2. Add Item" << endl;
    cout << "3. Delete Item" << endl;
    cout << "4. Exit" << endl;
    char ch = getch( );
    switch(ch){
        case '1': show_list( ); break;
        case '2': add_item( ); break;
        case '3': del_item( ); break;
        case '4': {updata( ), exit(0);}
        default:{
            system("cls");
            cout << "Invalid option. Please try again." << endl;
            system("pause");
        }
    }
    menue( );
}

int main( ){
    build( );
    menue( );
    return 0;
}
