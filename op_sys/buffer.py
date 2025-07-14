from os import *
from mmap import mmap

# dataファイルを作成して、バッファリングありでオープン
fd = open('data', O_CREAT | O_RDWR)

# 4KBのバッファを確保
buf = mmap(-1, 4096)

# 40MB(=4KB*10240)のデータを書き込み
for i in range(10240):
    write(fd, buf)

# ファイルをクローズ
close(fd)
