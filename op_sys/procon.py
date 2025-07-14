from threading import Thread, Semaphore, Lock

# バッファサイズ
buf_size = 4

# バッファ内のデータ数
data_size = 0

# 生産者の処理
def produce():
    global sem_data, sem_space
    global data_size
    
    for i in range(20):
        # セマフォの待機(Wait)
        sem_space.acquire()

        # データをバッファに追加
        lock.acquire()
        data_size += 1
        print('add (data = {})'.format(data_size))
        lock.release()

        # セマフォの通知(Signal)
        sem_data.release()

# 消費者の処理
def consume():
    global sem_data, sem_space
    global data_size
    
    for i in range(20):
        # セマフォの待機(Wait)
        sem_data.acquire()

        # データをバッファから削除
        lock.acquire()
        data_size -= 1
        print('remove (data = {})'.format(data_size))
        lock.release()
        
        # セマフォの通知(Signal)
        sem_space.release()

# ２つのセマフォの作成(Init)
sem_data = Semaphore(0)
sem_space = Semaphore(buf_size)

lock = Lock()

# 生産者と消費者のスレッドを作成
producer = Thread(target=produce)
consumer = Thread(target=consume)

producer.start()
consumer.start()

producer.join()
consumer.join()
