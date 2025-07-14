from multiprocessing import Process
from time import sleep

# プロセス数
n = 4

# 無限ループ
def loop():
    while True:
        pass
    
if __name__ == '__main__':        
    # プロセスのリスト
    plist = []
    
    # n個のプロセスを生成
    for i in range(n):
        p = Process(target=loop, daemon=True)
        plist.append(p)
        
    # n個のプロセスの実行を開始
    for p in plist:
        p.start()
        print('start process')
    
    # 20秒待つ
    sleep(20)
