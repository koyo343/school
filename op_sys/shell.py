from os import *

while True:
    # 絶対パスでプログラムと引数を入力
    cmd = input('> ')
    args = cmd.split()

    # 新しいプロセスを生成（プロセスIDを返す）
    pid = fork()

    # if文の範囲はカッコの代わりにインデントで指定
    if pid == 0:
        # 子プロセスの処理
        print('---- child ----')
        
        # 入力されたプログラムを実行
        execv(args[0], args)
    else:
        # 親プロセスの処理
        # 子プロセスの終了を待つ
        wait()
        
        print('---- parent ----')
