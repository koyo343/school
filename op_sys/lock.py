from multiprocessing import Process, Value, Lock

# プロセス１が実行する関数
def func1(n, lock):
    for i in range(500000):
        # ロックを獲得(Lock)
        lock.acquire()
        
        # 危険区域
        n.value = n.value + 1

        # ロックを解放(Unlock)
        lock.release()

# プロセス２が実行する関数（func1と同じ）
def func2(n, lock):
    for i in range(500000):
        lock.acquire()
        n.value = n.value + 1
        lock.release()

if __name__ == '__main__':
    # 共有変数n
    n = Value('i', 0)
    
    # ロック（共有変数）を作成
    lock = Lock()
    
    p1 = Process(target=func1, args=(n, lock))
    p2 = Process(target=func2, args=(n, lock))
    
    p1.start()
    p2.start()
    
    p1.join()
    p2.join()
    
    print(n.value)
