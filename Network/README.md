# Network - C言語によるTCPソケット通信

## 概要
C言語でTCPソケット通信を実装してみました。
サーバーとクライアント間でメッセージを送受信します。

## 構成
- server.c : TCPサーバー（bind・listen・accept）
- client.c : TCPクライアント（connect・send・recv）

## 通信の流れ
サーバー側              クライアント側
socket()               socket()
bind()
listen()
accept()    ←接続←    connect()
read()      ←送信←    write()
write()     →送信→     read()
close()                close()

## 実行方法
### サーバーを起動
gcc server.c -o server
./server

### クライアントを起動（別ターミナル）
gcc client.c -o client
./client

## 学んだこと
- ソケットの仕組み（socket・bind・listen・accept・connect）
- ファイルディスクリプタの概念
- ネットワークバイトオーダー（htons）