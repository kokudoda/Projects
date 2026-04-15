#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

/*  
    サーバー側の手順
    ・socket()
    ・bind()  で初期化処理
        ↓
    ・listen()　で接続受理準備(クライアントからの接続を待つ状態)
        ↓
    ・accept() 接続要求受理(クライアントからの接続要求を受理)
        ↓
    ・read()/write()  で読み込み/書き込み
        ↓
    ・close() 終了
*/ 

/* bind(int sockfd,struct sockaddr *my_addr,socklen_t addrlen) ディスクリプタをクライアントからの接続要求を受信するポート番号に結び付ける処理
                                                            ソケットに名前を付ける。返り値は正常終了で0、異常終了で-1
    sockfd にはファイルディスクリプタ(ソケット)を指定
    my_addr には接続要求を受信するアドレス、ポートを指定
    addrlen　には第二引数で渡した構造体のサイズ
*/

/* listen(int sock,int backlog) ファイルディスクリプタをクライアントからの接続要求受信待ち状態に移行させる処理
                                返り値は正常終了で0、異常終了で-1
    sock　にはファイルディスクリプタ
    backlog　には同時に受け付けるコネクションの最大数。とりあえず5にする
*/

/* accept(int sock,struct sockaddr *addr,socklen_t *addrlen) クライアントからの接続要求を受理し、クライアントとのデータの送受信を行うディスクリプタを
                                                            新たに生成する。返り値は正常終了でファイルディスクリプタ、異常終了で-1
    sock　には接続要求を受けたファイルディスクリプタ
    addr
    addr_len には*addrのサイズ                                            
*/

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE];

    //ソケット作成
    int server_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server_fd < 0){
        perror("socket");
        exit(1);
    }

    //アドレス設定
    memset(&addr,0,sizeof(addr));
    addr.sin_family = PF_INET; //IPv4
    addr.sin_addr.s_addr = INADDR_ANY; //すべてのネットワークインターフェースで接続を受ける
    addr.sin_port = htons(PORT); //ネットワークバイトオーダーに変換する

    //バインド
    if(bind(server_fd,(struct sockaddr *)&addr,sizeof(addr)) < 0){
        perror("bind");
        exit(1);
    }

    //接続要求受信待ち状態に移行
    if(listen(server_fd,5) < 0){
        perror("listen");
        exit(1);
    }

    printf("Server listening on port %d...\n",PORT);

    //接続受付
    socklen_t addrlen = sizeof(addr);
    int client_fd = accept(server_fd,(struct sockaddr *)&addr,&addrlen);
    if(client_fd < 0){
        perror("accept");
        exit(1);
    }

    //受信
    int n = read(client_fd,buffer,BUFFER_SIZE-1);
    if(n < 0){
        perror("read");
        exit(1);
    }
    buffer[n] = '\0';
    printf("Received: %s\n",buffer);

    //送信
    write(client_fd,"Hello from server",17);

    close(client_fd);
    close(server_fd);

    return 0;
}