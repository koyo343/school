from threading import Thread

# スレッド数
n = 3

# スレッド番号をゆっくり表示させるための待ち時間
count = 1000

start = False

# スレッドiが実行する関数
def func(i):
    global start

    # startがTrueになるまで待つ 
    while not start:
        pass
    
    # スレッド番号を1000回表示
    for j in range(1000):
        print(i, end='', flush=True)

        # ビジーウェイト
        for k in range(count):
            pass

# スレッドのリスト
tlist = []

# n個のスレッドを生成
for i in range(n):
    t = Thread(target=func, args=(i,))
    tlist.append(t)

# n個のスレッドの実行を開始
for t in tlist:
    t.start()

# スレッドによる表示を同時に開始
start = True

# n個のスレッドの終了を待つ
for t in tlist:
    t.join()

print('')
