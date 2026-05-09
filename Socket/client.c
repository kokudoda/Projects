#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


/*
クライアント側の手順
    socet()
    connect() で初期化処理
        ↓
    read()/write()　で読み込み/書き込み
        ↓
    close() で終了処理
*/

/*socket(int domain,int type,int protocol) はソケットを作るシステムコール。ファイルディスクリプタを返す(エラーなら-1を返す)
  domain にはプロトコルファミリ(IPv4ならPF_INET)
  type　には通信方法(TCPならSOCK_STREAM。UDPならSOCK_DGRAM)
  protocol　には通信に利用するプロトコル(TCPならIPPROTO_TCP、UDPならIPPROTO_UDP)。PF_INET,SOCK_STREAMを指定した場合は0と指定してもよい
  例　sockfd = socket(PF_INET,SOCK_STREA,IPPROTO_TCP);
*/

/*
struct sockaddr_in
├── sin_family   → IPv4かIPv6か
├── sin_port     → ポート番号
└── sin_addr     → IPアドレス

struct sockaddr_in addr; 
*/

/*connect(int sockfd,const struct sockaddr *serv_addr,socklen_t addrlen)接続する相手を指定し、ストリームをつなぐ。IPアドレスとポート番号を扱う。
                                (UDPで通信を行う場合はconnect()を使用しなくてもよい)。返り値は成功したら0、失敗したら-1
    sockfd にはファイルディスクリプタを指定する。socket()で帰ってきた値
    serv_addr
    addrlen には第二引数で渡した構造体のサイズを指定する
    例 
*/

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    //ソケット作成
    int fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd < 0){
        perror("socket");
        exit(1);
    }

    //サーバー情報設定
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(PF_INET,"127.0.0.1",&server_addr.sin_addr);

    //接続
    if(connect(fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0){
        perror("connect");
        exit(1);
    }

    //送信
    write(fd,"Hello from client",17);

    //受信
    int n = read(fd,buffer,BUFFER_SIZE-1);
    if(n < 0){
        perror("read");
        exit(1);
    }
    buffer[n] = '\0';
    printf("Received: %s\n",buffer);

    close(fd);

    return 0;
}