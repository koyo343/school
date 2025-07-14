from multiprocessing import Process, Value

# プロセス１が実行する関数
def func1(n):
    # nの値を1ずつ50万回増やす
    for i in range(500000):
        # 危険区域
        n.value = n.value + 1

# プロセス２が実行する関数（func1と同じ）
def func2(n):
    for i in range(500000):
        n.value = n.value + 1

if __name__ == '__main__':        
    # 共有変数n
    n = Value('i', 0)

    # ２つのプロセスを生成
    p1 = Process(target=func1, args=(n,))
    p2 = Process(target=func2, args=(n,))
    
    # ２つのプロセスの実行を開始
    p1.start()
    p2.start()
    
    # ２つのプロセスの終了を待つ
    p1.join()
    p2.join()
    
    # nの値を表示（期待する値は100万）
    print(n.value)
