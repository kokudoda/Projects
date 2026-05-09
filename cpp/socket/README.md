# C++によるTCPソケット通信

## 概要
C++のクラスを使ってTCPソケット通信を実装しました。
サーバーとクライアントがCtrl+Dを押すまで
メッセージを送り合えます。

## ファイル構成
```
├── client_socket.hpp  // Clientクラスの定義
├── server_socket.hpp  // Serverクラスの定義
├── client.cpp         // クライアントのmain関数
└── server.cpp         // サーバーのmain関数
```

## クラス設計

### Clientクラス
| メソッド | 役割 |
|---|---|
| Client() | socket()でソケット作成 |
| connection() | connect()でサーバーに接続 |
| send() | メッセージを送信 |
| receive() | メッセージを受信 |
| ~Client() | close()でソケットを閉じる |

### Serverクラス
| メソッド | 役割 |
|---|---|
| Server() | socket()でソケット作成 |
| server_bind() | bind()でポートに紐付け |
| server_listen() | listen()で接続待ち |
| server_accept() | accept()で接続受理 |
| send_msg() | メッセージを送信 |
| receive() | メッセージを受信 |
| ~Server() | close()でソケットを閉じる |

## 通信の流れ
```
Server              Client
socket()            socket()
bind()
listen()
accept()    ←接続←  connect()
receive()   ←送信←  send()
send_msg()  →送信→  receive()
↑Ctrl+Dまで繰り返しますわ
```

## 実行方法
### コンパイル
```bash
g++ -o server server.cpp
g++ -o client client.cpp
```

### 実行（ターミナルを2つ開きます）
```bash
# ターミナル1
./server

# ターミナル2
./client
```

### 終了
```
Ctrl + D
```

## 学んだこと
- C++のクラスでソケット通信を設計する方法
- server_fdとclient_fdの役割の違い
- コンストラクタ・デストラクタでリソース管理する方法