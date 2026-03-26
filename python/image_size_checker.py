from PIL import Image
import os
import glob     #globでファイル名の配列を取得する
from dotenv import load_dotenv

load_dotenv()   #.envの内容を環境変数に追加しますわ
  
path = os.getenv("Screenshots_path")    #環境変数を取得する
images = glob.glob(path)  #screenshotsフォルダ内の.pngファイルを取得する

total = 0.0

for image in images:  
    ##print(image)    #ファルダ内の.pngファイルを表示する

    file_size_bytes = os.path.getsize(image)      #os.path.getsize()でファイルのサイズを取得
    total += file_size_bytes / (1024 * 1024)      #フォルダ内の.pngファイルの大きさの合計.MB単位に変換

print(f"ファイルサイズ: {total:.2f} MB")  

