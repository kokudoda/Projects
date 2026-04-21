#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstdio> 
#include <iostream>

#define BUFFER_SIZE 1024

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Server{
    private:
        int server_fd; //3ウェイハンドシェイク用のファイルディスクリプタ(bind,listen用)
        int client_fd; //実際の通信用のファイルディスクリプタ(accept,read,write用)
    public:
        Server();
        ~Server();
        void server_bind(int port);
        void server_listen();
        void server_accept();
        void send_msg(string s);
        void receive();
};

//コンストラクタ
Server::Server()
{
    server_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server_fd < 0){
        perror("socket");
        exit(1);
    }
}

//デストラクタ
Server::~Server()
{
    close(server_fd);
    close(client_fd);
}

//ディスクリプタをクライアントからの接続要求を受信するポート番号(今回は8080)に結び付ける処理
void Server::server_bind(int port)
{
    /*
     struct sockaddr_in
        ├── sin_family   → IPv4(PF_INET)かIPv6(PF_INET6)か
        ├── sin_port     → ポート番号
        └── sin_addr     → IPアドレス

        struct sockaddr_in addr; 
    */
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(1);
    }
}

//ファイルディスクリプタをクライアントからの接続要求受信待ち状態に移行させる処理
void Server::server_listen()
{
    if(listen(server_fd,5) < 0){
        perror("listen");
        exit(1);
    }
}
//クライアントからの接続要求を受理し、クライアントとのデータの送受信を行うディスクリプタを新たに生成する
void Server::server_accept()
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr); //accept()で使用される、アドレスの長さを格納する型。
    client_fd = accept(server_fd,(struct sockaddr* )&addr,&addrlen);
    if(client_fd < 0){
        perror("accept");
        exit(1);
    }
}

//送信する関数
void Server::send_msg(string s)
{   
    write(client_fd,s.c_str(),s.size());
}

//受け取る関数
void Server::receive()
{
    char buffer[BUFFER_SIZE];
    int n = read(client_fd,buffer,BUFFER_SIZE-1);
    if(n < 0){
        perror("read");
        exit(1);
    }
    buffer[n] = '\0';
    cout << "Received : " << buffer << endl;
}