#include "client_socket.hpp"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
    Client client1;
    client1.connection("127.0.0.1",8080); //ipアドレスは127.0.0.1(ローカルループバックアドレス),ポート番号8080

    while(1){
        cout << " >>> ";
        string str;
        if(!(cin >> str)) break;

        client1.send(str);
        client1.receive();
    }
    return 0;
}