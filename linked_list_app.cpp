#include <iostream>
using namespace std;

struct Node{
    int data;
    struct Node* next;
};

//ポインタを書き換えるためにダブルポインタを使う

struct Node* make_node(int data);//ノードを作る関数
void add_front(struct Node** head,struct Node** tail,int data); //先頭に追加する関数
void add_rear(struct Node** head,struct Node** tail,int data); //末尾に追加する関数
void delete_front(struct Node** head,struct Node** tail); //先頭を削除する関数
void show(struct Node* head); //表示する関数
void search(struct Node* head,int key); //探索する関数
void free_node(struct Node** head,struct Node** tail); //ノードを開放する関数


int main()
{
    struct Node* head = nullptr; //先頭を指すポインタ
    struct Node* tail = nullptr; //末尾を指すポインタ
    int choice; 
    int data,key;

    while(true){
        cout << "1 : add in front" << endl;  //add_front()
        cout << "2 : add in rear" << endl;   //add_rear()
        cout << "3 : delete front" << endl;  //delete_front()
        cout << "4 : show" << endl;          //show()
        cout << "5 : search" << endl;        //search()
        cout << "6 : end" << endl;     

        cout << " >> ";
        cin >> choice;

        switch(choice){
        case 1: //先頭に追加
            cout << " >> ";
            cin >> data;
            add_front(&head,&tail,data);
            cout << endl;
            break;
        case 2: //末尾に追加
            cout << " >> ";
            cin >> data;
            add_rear(&head,&tail,data);
            cout << endl;
            break;
        case 3: //先頭を削除
            cout << "delete front" << endl;
            delete_front(&head,&tail);
            cout << endl;
            break;
        case 4: //表示
            show(head);
            cout << endl;
            break;
        case 5: //検索
            cout << " >> " ;
            cin >> key;
            search(head,key);
            cout << endl;
            break;
        case 6: //終了
            cout << "end" << endl;
            free_node(&head,&tail);
            return 0;
        default: //エラー
            cout << "type it agein" << endl;
            break;
        }
    }

}

struct Node* make_node(int data)
{
    struct Node* node = new struct Node; //メモリ確保
    if(node == nullptr){ //確保できなかった場合
        return nullptr;
    }
    node->data = data;
    node->next = nullptr;

    return node;
}

void add_front(struct Node** head,struct Node** tail,int data)
{
    struct Node* new_node = make_node(data);
    if(new_node == nullptr){
        cout << "could not allocate memory" << endl;
        return ;
    }
    if(*head == nullptr){
        *head = new_node;
        *tail = new_node;
        return ;
    }
    new_node->next = *head;
    *head = new_node;
}

void add_rear(struct Node** head,struct Node** tail,int data)
{
    struct Node* new_node = make_node(data);
    if(new_node == nullptr){
        cout << "could not allocate memory" << endl;
        return ;
    }
    if(*head == nullptr){
        *head = new_node;
        *tail = new_node;
        return ;
    }
    
    (*tail)->next = new_node;
    *tail = new_node;
}

void delete_front(struct Node** head,struct Node** tail)
{
    if(*head == nullptr){
        cout << "EMPTY" << endl;
        return ;
    }
    struct Node* temp = *head;
    *head = temp->next;
    if(*head == nullptr){
        *tail = nullptr;
    }
    cout << "delete : " << temp->data << endl;
    delete temp;
}

void show(struct Node* head)
{
    while(head){
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

void search(struct Node* head,int key)
{
    while(head){
        if(head->data == key){
            cout << "[" << key << "] found!" << endl;
            return ;
        }
        head = head->next;
    }
    cout << "Not found" << endl;
}

void free_node(struct Node** head,struct Node** tail)
{
    struct Node* current = *head;
    while(current){
        struct Node* temp = current->next; //次のノードを指すポインタ
        delete current;
        current = temp;
    }
    *head = nullptr; //ダングリングポインタ防止
    *tail = nullptr;
}