import requests
import time
from plyer import notification   #通知を出すため

CLIENT_ID = "自分のTWITCH ID"       
CLIENT_SECRET = "自分のTWITCH シークレット"    
target_channel = "kato_junichi0817"                 #目的のチャンネル
CHECK_INTARVAL = 60                                 #60秒ごとにチェック


#アクセストークンを取得する関数
def get_access_token():
    url = "https://id.twitch.tv/oauth2/token"  #twitchサーバーのurl トークンを貰うためのurl

    #Twitchサーバーに送る情報を辞書でまとめる
    data = {
        "client_id" : CLIENT_ID,
        "client_secret" : CLIENT_SECRET,
        "grant_type" : "client_credentials" #アプリ同士の通信で必要
    }

    response = requests.post(url,data=data)

    #print(response.text)  #デバッグ用
    result = response.json()    #返答をpython辞書に変換
    return  result["access_token"]
""""
レスポンスで帰ってくる値
{
  "access_token": "jostpf5q0uzmxmkba9iyug38kjtgh",
  "expires_in": 5011271,
  "token_type": "bearer"
}

"""
#配信しているかどうか確認する関数
def is_live(access_token):

    #配信状況を問い合わせるTwitchサーバーのurl
    url = "https://api.twitch.tv/helix/streams"      

    #認証済みである情報
    headers = {
        "Client-id" : CLIENT_ID,
        "Authorization" : f"Bearer {access_token}"
    }

    #誰の配信状況をしらべたいか
    parameter = {"user_login" : target_channel}

    #サーバーに問い合わせる(リクエスト).get(問い合わせ先, 認証情報, 誰の配信状況か)
    response = requests.get(url,headers=headers,params=parameter)
    """
    getの引数(url,)
    curl -X GET
    'https://api.twitch.tv/helix/streams?user_login=afro&user_login=cohhcarnage&user_login=lana_lux' \
    -H 'Authorization: Bearer 2gbdx6oar67tqtcmt49t3wpcgycthx' \
    -H 'Client-Id: uo6dggojyb8d6soh92zknwmi5ej1q2'
    """
    data = response.json()

    #配信していたらTrueを返す
    return len(data["data"]) > 0
    """
    配信していないときは↓が空("data":[],)となるので >0としている
    {
  "data": [
    {
      "id": "40952121085",
      "user_id": "101051819",
      "user_login": "afro",
      ...
    },
    ...
  ],
  "pagination": {}
}
    """



#通知を出す関数
def send_notifiation(title,message):
    notification.notify(
        title = title,
        message = message,
        timeout = 10
    )


def main():
    print("Twitchうんこちゃん通知アプリ")
    print(f"{CHECK_INTARVAL}秒ごとに配信をチェック")
    print("終了するには Ctrl+C を押してください\n")
    
    #アクセストークンの取得
    access_token = get_access_token()
    print("アクセストークンの取得に成功しました")

    was_live = False

    while True:
        try:
            live = is_live(access_token)

            if live and not was_live:
                print("配信を開始しました")
                send_notifiation(
                    title = "うんこちゃんが配信を開始しました",
                    message = "Twitchを開こう"
                )
                was_live = True
            
            elif not live and was_live:
                print("配信が終了しました")
                was_live = False

            else:
                status = "配信中です" if live else "配信していません"
                print(f"[{status}]")

            time.sleep(CHECK_INTARVAL)

        except KeyboardInterrupt:
            print("\n終了します")
            break

        except Exception as e:
            print(f"エラーが発生しました : {e}")
            print("60秒後に再試行します")
            time.sleep(60)

if __name__ == "__main__":
    main()