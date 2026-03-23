#include <iostream>
using std::cout;
using std::cin;

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
        cout << "EMPTY" << "\n";
        return ;
    }
    Node* temp = head;
    head = temp->next;
    if(head == nullptr){ //headがnullptrを指したらtailもnullptrを指すようにする
        tail = nullptr;
    }
    cout << "delete : " << temp->data << "\n"; 
    delete temp;
}

void Linked_List::show()
{
    Node* temp = head;

    while(temp){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << "\n";
}

void Linked_List::search(int key)
{
    Node* temp = head;

    if(temp == nullptr){
        cout << "EMPTY" << "\n";
        return ;
    }
    while(temp){
        if(temp->data == key){
            cout << "[" << key << "] found" << "\n";
            return ;
        }
        temp = temp->next;
    }
    cout << "Not found" << "\n";
}

void Linked_List::free_node()
{
    Node* current = head;
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
        cout << "1 : add in front" << "\n";   //add_front()
        cout << "2 : add in rear" << "\n";   //add_rear()
        cout << "3 : delete front" << "\n";   //delete_front()
        cout << "4 : show" << "\n";     //show()
        cout << "5 : search" << "\n";     //search()
        cout << "6 : end" << "\n";     //end

        cout << " >> ";
        cin >> choice;
        
        int data,key;
        switch(choice){
            case 1:
                cout << "Please enter the number you would like to add >> ";
                cin >> data;
                list.add_front(data);
                cout << "\n";
                break;

            case 2:
                cout << "Please enter the number you would like to add >> ";
                cin >> data;
                list.add_rear(data);
                cout << "\n";
                break;

            case 3:
                cout << "delete front" << "\n";
                list.delete_front();
                cout << "\n";
                break;
            
            case 4:
                cout << "show" << "\n";
                list.show();
                cout << "\n";
                break;

            case 5:
                cout << "Please enter the number you want to search for >> ";
                cin >> key;
                list.search(key);
                cout << "\n";
                break;
                
            case 6:
                cout << "end" << "\n";
                return 0;

            default:
                cout << "invalid number" << "\n";
                cout << "\n";
                break;
        }        
    }
}