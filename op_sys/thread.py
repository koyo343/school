from threading import Thread
from time import sleep

start = 0

# スレッド１が実行する関数
def func1():
    # 大域変数startを使うことを宣言
    global start
    
    # startが1になるまで待つ
    while start == 0:
        pass
    
    # 10回表示
    for i in range(10):
        # 計算
        sum = 0
        for k in range(100):
            sum += k
        
        print('thread 1')

# スレッド２が実行する関数
def func2():
    global start

    while start == 0:
        pass
    
    for i in range(10):
        # 計算
        sum = 0
        for k in range(100):
            sum += k
        
        print('thread 2')

# ここからmain関数の処理
        
# スレッドを２つ生成
t1 = Thread(target=func1)
t2 = Thread(target=func2)

# スレッドの実行を開始
t1.start()
t2.start()

# スレッドによる表示を同時に開始
start = 1

# スレッドの終了を待つ
t1.join()
t2.join()
