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
    server.server_bind(8080);
    server.server_listen();
    server.server_accept();

    while(1){
        server.receive();

        cout << " >>> ";
        string str;
        if(!(cin >> str)) break;

        server.send_msg(str);
    }

    return 0;

}