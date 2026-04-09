import requests
#import json

prefecture = {
    
    "北海道" : "https://www.jma.go.jp/bosai/forecast/data/forecast/016000.json",
    "青森県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/020000.json",
    "秋田県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/050000.json",
    "岩手県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/030000.json",
    "宮城県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/040000.json",
    "山形県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/060000.json",
    "福島県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/070000.json",
    "茨城県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/080000.json",
    "栃木県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/090000.json",
    "群馬県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/100000.json",
    "埼玉県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/110000.json",
    "東京都" : "https://www.jma.go.jp/bosai/forecast/data/forecast/130000.json",
    "千葉県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/120000.json",
    "神奈川県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/140000.json",
    "長野県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/200000.json",
    "山梨県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/190000.json",
    "静岡県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/220000.json",
    "愛知県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/230000.json",
    "岐阜県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/210000.json",
    "三重県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/240000.json",
    "新潟県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/150000.json",
    "富山県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/160000.json",
    "石川県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/170000.json",
    "福井県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/180000.json",
    "滋賀県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/250000.json",
    "京都府" : "https://www.jma.go.jp/bosai/forecast/data/forecast/260000.json",
    "大阪府" : "https://www.jma.go.jp/bosai/forecast/data/forecast/270000.json",
    "兵庫県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/280000.json",
    "奈良県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/290000.json",
    "和歌山県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/300000.json",
    "岡山県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/330000.json",
    "広島県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/340000.json",
    "島根県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/320000.json",
    "鳥取県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/310000.json",
    "徳島県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/360000.json",
    "香川県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/370000.json",
    "愛媛県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/380000.json",
    "高知県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/390000.json",
    "山口県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/350000.json",
    "福岡県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/400000.json",
    "大分県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/440000.json",
    "長崎県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/420000.json",
    "佐賀県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/410000.json",
    "熊本県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/430000.json",
    "宮崎県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/450000.json",
    "鹿児島県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/460100.json",
    "沖縄県" : "https://www.jma.go.jp/bosai/forecast/data/forecast/471000.json"
}

key = input("都道府県を入力してください >> ")

url = prefecture[key]

response = requests.get(url)
data = response.json()

print(data[0]["timeSeries"][0]["areas"][0]["weathers"][0])
#print(json.dumps(data, ensure_ascii=False, indent=2))
"""
[
  { data[0]

    "publishingOffice": "大阪管区気象台",
    "reportDatetime": "2026-04-01T17:00:00+09:00",
    "timeSeries": [
      { timeSeries[0]

        "timeDefines": [
          "2026-04-01T17:00:00+09:00",  今日
          "2026-04-02T00:00:00+09:00",  明日
          "2026-04-03T00:00:00+09:00"   明後日
        ],
        "areas": [
          { areas[0]

            "area": {
              "name": "大阪府",
              "code": "270000"
            },
            "weatherCodes": [
              "300",
              "102",
              "111"
            ],
            "weathers": [
              "雨",
              "くもり 後 晴れ 未明 雨",
              "晴れ 後 くもり"
            ],
            "winds": [
              "北の風 海上 では 北の風 やや強く",
              "北西の風 海上 では 北西の風 やや強く",
              "北東の風 後 南西の風"
            ],
            "waves": [
              "０．５メートル 後 １メートル",
              "１メートル",
              "０．５メートル"
            ]
          }
        ]
      },
"""