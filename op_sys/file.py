from random import randrange

# 順アクセス
def seq_access():
    # このファイル自身をオープン
    f = open('file.py')

    for i in range(10):
        # ファイルポインタを表示
        ptr = f.tell()
        print(ptr)

        # 1バイト読み込み
        data = f.read(1)

    # ファイルポインタを表示
    ptr = f.tell()
    print(ptr)

    # ファイルをクローズ
    f.close()
        
# ランダムアクセス
def rnd_access():
    f = open('file.py')

    for i in range(10):
        # 0〜9の乱数を生成
        k = randrange(10)

        # ファイルポインタをkバイト目に移動
        f.seek(k)
    
        # ファイルポインタを表示
        ptr = f.tell()
        print(ptr)

        data = f.read(1)

    f.close()

print('sequential access')
seq_access()

print('')

print('random access')
rnd_access()
