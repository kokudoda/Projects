#include <iostream>
using namespace std;

//クラスで実装

class Node{
    public:
        int data;
        Node* next;
        Node(int val) : data(val),next(nullptr){} //コンストラクタ
};

class Linked_List{
    private:    
        Node* head;
        Node* tail;
    public:
        Linked_List() : head(nullptr),tail(nullptr){} //コンストラクタ
        ~Linked_List(){ //デストラクタ
            free_node();
        };
        void add_front(int data);
        void add_rear(int data);
        void delete_front();
        void show();
        void search(int key);
        void free_node();
};

void Linked_List::add_front(int data)
{
    Node* new_node = new Node(data);
    if(head == nullptr){ //まだ何も入ってないとき
        head = new_node;
        tail = new_node;
        return ;
    }
    new_node->next = head;
    head = new_node;
}

void Linked_List::add_rear(int data)
{   
    Node* new_node = new Node(data);
    if(head == nullptr){ //まだ何も入っていないとき
        head = new_node;
        tail = new_node;
        return ;
    }
    tail->next = new_node;
    tail = new_node;
}

void Linked_List::delete_front()
{
    if(head == nullptr){
        cout << "EMPTY" << endl;
        return ;
    }
    Node* temp = head;
    head = temp->next;
    if(head == nullptr){ //headがnullptrを指したらtailもnullptrを指すようにする
        tail = nullptr;
    }
    cout << "delete : " << temp->data << endl; 
    delete temp;
}

void Linked_List::show()
{
    Node* temp = head;

    while(temp){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

void Linked_List::search(int key)
{
    Node* temp = head;

    if(temp == nullptr){
        cout << "EMPTY" << endl;
        return ;
    }
    while(temp){
        if(temp->data == key){
            cout << "[" << key << "] found" << endl;
            return ;
        }
        temp = temp->next;
    }
    cout << "Not found" << endl;
}

void Linked_List::free_node()
{
    struct Node* current = head;
    while(current){
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = nullptr; //ダングリングポインタ防止
    tail = nullptr;
}

int main()
{
    Linked_List list;
    int choice;

    while(1){
        cout << "1 : add in front" << endl;   //add_front()
        cout << "2 : add in rear" << endl;   //add_rear()
        cout << "3 : delete front" << endl;   //delete_front()
        cout << "4 : show" << endl;     //show()
        cout << "5 : search" << endl;     //search()
        cout << "6 : end" << endl;     //end

        cout << " >> ";
        cin >> choice;
        
        int data,key;
        switch(choice){
            case 1:
                cout << "Please enter the number you would like to add >> ";
                cin >> data;
                list.add_front(data);
                cout << endl;
                break;

            case 2:
                cout << "Please enter the number you would like to add >> ";
                cin >> data;
                list.add_rear(data);
                cout << endl;
                break;

            case 3:
                cout << "delete front" << endl;
                list.delete_front();
                cout << endl;
                break;
            
            case 4:
                cout << "show" << endl;
                list.show();
                cout << endl;
                break;

            case 5:
                cout << "Please enter the number you want to search for >> ";
                cin >> key;
                list.search(key);
                cout << endl;
                break;
                
            case 6:
                cout << "end" << endl;
                return 0;

            default:
                cout << "invalid number" << endl;
                cout << endl;
                break;
        }        
    }
}