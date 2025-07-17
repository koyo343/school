import os
from time import time

data_size = 40

mem_size = os.sysconf('SC_PAGE_SIZE') * os.sysconf('SC_PHYS_PAGES')
data_num = int(mem_size / data_size)

# メモリ4GBにつき約1億個のデータを持つリストを作成
data = list(range(data_num))

print('allocated')


# １回目（ページイン）
start = time()

# 先頭の1/5のデータにアクセス
sum = 0
for i in range(int(data_num / 5)):
    sum += data[i]

print('1st: {:.1f} sec'.format(time() - start))


# ２回目（ページインなし）
start = time()

# 先頭の1/5のデータにアクセス
sum = 0
for i in range(int(data_num / 5)):
    sum += data[i]

print('2nd: {:.1f} sec'.format(time() - start))
