import os
from time import sleep

data_size = 40

mem_size = os.sysconf('SC_PAGE_SIZE') * os.sysconf('SC_PHYS_PAGES')
data_num = int(mem_size / data_size)

# メモリ4GBにつき約1億個のデータを持つリストを作成
data = list(range(data_num))

print('allocated')

sleep(60)
