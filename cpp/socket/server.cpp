#include "server_socket.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
    Server server;
    server.server_bind(8080); //ポート番号は8080を指定
    server.server_listen();
    server.server_accept();

    while(1){
        server.receive();

        cout << " >>> ";
        string str;
        if(!(cin >> str)) break; //Ctrl+Dが押されるまで

        server.send_msg(str);
    }

    return 0;

}