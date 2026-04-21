#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstdio> 
#include <iostream>

using std::string;
using std::cout;
using std::endl;

#define BUFFER_SIZE 1024

class Client{
    private:
        int fd; //ファイルディスクリプタ
    public: 
        Client();
        ~Client();
        void connection(const char* ip,int port);
        void send(string s);
        void receive();
};

//コンストラクタ
Client::Client()
{
    fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd < 0){
        perror("socket");
        exit(1);
    }
}

//デストラクタ
Client::~Client()
{
    close(fd);
}

//接続する相手を指定し、ストリームをつなぐ関数
void Client::connection(const char* ip,int port)
{
    struct sockaddr_in server_addr;

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(PF_INET,ip,&server_addr.sin_addr);

    if(connect(fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0){
        perror("connect");
        exit(1);
    }
}

//送信する関数
void Client::send(string s)
{
    write(fd,s.c_str(),s.size());
    //s.c_str()はC++の文字列をC言語の文字列表記に変換する
}

//受信する関数
void Client::receive()
{
    char buffer[BUFFER_SIZE]; //受け取る配列
    int n = read(fd,buffer,BUFFER_SIZE-1);
    if(n < 0){
        perror("read");
        exit(1);
    }
    buffer[n] = '\0';
    cout << "Received : " << buffer << endl;
}