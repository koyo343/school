from multiprocessing import Process, Value

# プロセス１が実行する関数
def func1(n, turn, c1, c2):
    for i in range(500000):
        c1.value = 0

        while c2.value == 0:
            if turn.value == 2:
                c1.value = 1
                while turn.value == 2:
                    pass
                c1.value = 0
        
        # 危険区域
        n.value = n.value + 1

        c1.value = 1
        turn.value = 2
        
# プロセス２が実行する関数
def func2(n, turn, c1, c2):
    for i in range(500000):
        c2.value = 0

        while c1.value == 0:
            if turn.value == 1:
                c2.value = 1
                while turn.value == 1:
                    pass
                c2.value = 0
        
        # 危険区域
        n.value = n.value + 1

        c2.value = 1
        turn.value = 1

if __name__ == '__main__':        
    # 共有変数n
    n = Value('i', 0)
    
    # Dekkerのアルゴリズムで使う共有変数
    turn = Value('i', 1)
    c1 = Value('i', 1)
    c2 = Value('i', 1)
    
    p1 = Process(target=func1, args=(n, turn, c1, c2))
    p2 = Process(target=func2, args=(n, turn, c1, c2))
    
    p1.start()
    p2.start()
    
    p1.join()
    p2.join()
    
    print(n.value)
