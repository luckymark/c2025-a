#include<bits/stdc++.h>
using namespace std;

struct LIST{
    struct node{
        int val;
        node *nxt;
    };
    node *head;
    void build( ){
        int n; cin >> n;
        node *now = nullptr, *lst = nullptr;
        while(n--){
            int x; cin >> x;
            now = (node*)malloc(sizeof(node));
            now->val = x;
            now->nxt = nullptr;
            if(head == nullptr) head = now;
            else lst->nxt = now;
            lst = now;
        }
        now = head;
    }
    void reverse( ){
        node *now = head, *lst = nullptr;
        while(now != nullptr){
            if(lst == nullptr){
                lst = now;
                now = now->nxt;
            }
            else{
                node *p = now->nxt;
                now->nxt = lst;
                lst = now;
                now = p;
            }
        }
        head->nxt = nullptr;
        head = lst;
    }
    int find(int val, int rnk){
        node *now = head;
        int cnt = 1;
        while(now != nullptr){
            if(now->val == val){
                rnk--;
                if(!rnk) return cnt;
            }
            now = now->nxt;
            cnt++;
        }
        return -1;
    }
    void peek( ){
        node *now = head;
        while(now != nullptr){
            cout << now->val << " ";
            now = now->nxt;
        }
        cout << '\n';
        return;
    }
} lst;

int main( ){
    lst.build( );
    lst.reverse( );
    cout << lst.find(5, 1) << endl;
    cout << lst.find(5, 2) << endl;
    return 0;
}
