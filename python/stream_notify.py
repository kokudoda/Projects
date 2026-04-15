import requests
from plyer import notification  #通知機能
import time
from dotenv import load_dotenv
import os

load_dotenv()   #.envファイルの読み込み

CLIENT_ID = os.getenv("CLIENT_ID")      #自分のクライアントID
CLIENT_SECRET = os.getenv("CLIENT_SECRET")      #自分のクライアントシークレット
Target = "kato_junichi0817"     #配信者

CHECK_INTARVAL = 60            #60秒ごとにチェック

img = os.getenv("IMG")  #send_notification()で出す通知のアイコン画像

#トークンを取得する関数
def get_token():
    url = "https://id.twitch.tv/oauth2/token"   #目的のurl
    
    """ <POSTリクエストの例↓>
    client_id=hof5gwx0su6owfnys0yan9c87zr6t         クライアントid
    &client_secret=41vpdji4e9gif29md0ouet6fktd2     クライアントシークレット
    &grant_type=client_credentials                  grant_type
    """

    data = {    #↑を参考に
        "client_id" : CLIENT_ID,
        "client_secret" : CLIENT_SECRET,
        "grant_type" : "client_credentials"
    }
    response = requests.post(url,data=data)
    result = response.json()

    """"
    レスポンスで帰ってくる値
    {
    "access_token": "xxxxxxxxxxxxxxxxxxx",
    "expires_in": xxxxxxx,
    "token_type": "bearer"
    }
    """

    return result["access_token"]

    
#配信しているかどうか調べる関数
def is_live(access_token):
    url = "https://api.twitch.tv/helix/streams"     #Get Streamsのリクエスト先

    """ <getリクエストの例↓>
    curl -X GET
        'https://api.twitch.tv/helix/streams?user_login=afro&user_login=cohhcarnage&user_login=lana_lux' \
        -H 'Authorization: Bearer xxxxxxxxxxxxxxxxx' \
        -H 'Client-Id: xxxxxxxxxxxxxxxxxxxxxx'
    """

    headers = {     #-H なのでヘッダー(headers)
        "Authorization" : f"Bearer {access_token}",     #Beare認証
        "Client-Id" : CLIENT_ID     #自分のid
    }
    
    params = {      # ?user_loginなのでパラメータ(params)
        "user_login" : Target,      #調べたい配信者
    }

    response = requests.get(url,params=params,headers=headers)
    if response.status_code != 200:
        print("Error")
        return False,None,None,None
    
    #print(response.status_code)
    res_json = response.json()
    #print(res_json)
    if  res_json["data"]:    #"data" : []が空の時は配信はしていない
        stream_title = res_json["data"][0]["title"]            #配信タイトル
        game_name = res_json["data"][0]["game_name"]           #ゲーム名
        start_stream = res_json["data"][0]["started_at"]       #配信開始時刻

        return True,stream_title,game_name,start_stream
    else:
        return False,None,None,None
    

#ポップアップで通知する関数
def send_notification(stream_title,game_name):
    notification.notify(
        title = stream_title,
        message = game_name,
        app_icon = img,
        timeout = 10
    )

#通知したかどうか判断する関数
def check_notify(live,stream_title,game_name,start_stream,was_live):
    
    #配信していて、未通知のとき
    if live and not was_live:
        print(f"配信開始 : {start_stream}")
        send_notification(
            stream_title,
            game_name
        )
        return True     #通知したのでTrueにする
    
    #配信していないとき
    if not live:
        print("配信はしていません")
        return False
    
    return was_live

def main():

    print("うんこちゃん通知アプリです\n")
    print("終了は Ctrl+C です")


    access_token = get_token()
    print("トークンの取得に成功しました")

    was_live = False    #通知したかどうかのフラグ(通知済み:True , 未通知:False)

    while True:
        try:    #例外の発生を調べる
            live,stream_title,game_name,start_stream = is_live(access_token)

            was_live = check_notify(live,stream_title,game_name,start_stream,was_live)

            time.sleep(CHECK_INTARVAL)

        except KeyboardInterrupt:      #Ctrl + Cが押されたときの例外処理
            print("\n終了します")
            break

        except Exception as e:  #エラーが発生したとき
            print(f"エラーが発生しました : {e}")
            print("60秒後に再開します")
            time.sleep(60)

if __name__ == "__main__":
    main()