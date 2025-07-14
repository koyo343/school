import random
import copy

# メモリサイズ
memsize = 300

# メモリ領域の最大サイズ
maxsize = 40

# メモリ領域
class Region:
    # start: 開始アドレス
    # size: サイズ
    
    def __init__(self, start, size):
        self.start = start
        self.size = size

    def fitness(self, size):
        return self.size - size
        
    # メモリ領域を分割
    def split(self, size):
        if size > self.size:
            print('cannot split')
            return -1
        
        start = self.start
        self.start += size
        self.size -= size

        return start

    # メモリ領域の開始アドレスを比較
    def compare(self, region):
        return self.start - region.start

    # 前のメモリ領域とマージ
    def merge_prev(self, prev):
        if prev.start + prev.size == self.start:
            self.start = prev.start
            self.size += prev.size
            return True
        else:
            return False
            
    # 後のメモリ領域とマージ
    def merge_next(self, next):
        if self.start + self.size == next.start:
            self.size += next.size
            return True
        else:
            return False

    def print_range(self):
        end = self.start + self.size - 1
        print('[{}, {}]'.format(self.start, end), end='')
    
    def print_size(self):
        print('[{}]'.format(self.size), end='')

# メモリの割当て
# fitfunc: best_fit, worst_fit, first_fitのいずれか
def alloc(size, freelist, fitfunc):
    region = fitfunc(size, freelist)
    if region is None:
        return None
        
    start = region.split(size)
    new_region = Region(start, size)
    
    if region.size == 0:
        freelist.remove(region)

    return new_region

# ベストフィットで探索
def best_fit(size, freelist):
    best_fitness = 9999
    best_region = None
    
    for region in freelist:
        fitness = region.fitness(size)
        if fitness >= 0 and fitness < best_fitness:
            best_fitness = fitness
            best_region = region

    return best_region

# ワーストフィットで探索
def worst_fit(size, freelist):
    worst_fitness = -1
    worst_region = None
    
    for region in freelist:
        fitness = region.fitness(size)
        if fitness >= 0 and fitness > worst_fitness:
            worst_fitness = fitness
            worst_region = region

    return worst_region

# ファーストフィットで探索
def first_fit(size, freelist):
    for region in freelist:
        fitness = region.fitness(size)
        if fitness >= 0:
            return region

    return None

# メモリの解放
def free(region, freelist):
    # 空きリストが空の場合
    if not freelist:
        freelist.append(region)
        return
    
    for i, r in enumerate(freelist):
        if region.compare(r) < 0:
            freelist.insert(i, region)

            # 前後のメモリ領域とマージ
            if i - 1 >= 0:
                prev_region = freelist[i - 1]
                if region.merge_prev(prev_region):
                    freelist.remove(prev_region)
            if region.merge_next(r):
                freelist.remove(r)
            return

    # 空きリストの最後に追加される場合
    prev_region = freelist[-1]
    freelist.append(region)
    
    if region.merge_prev(prev_region):
        freelist.remove(prev_region)
        
def print_range(type, rlist):
    print(type + ': ', end='')
    for r in rlist:
        r.print_range()
    print('')

def print_size(type, rlist):
    print(type + ': ', end='')
    for r in rlist:
        r.print_size()
    print('')

# ３つのアルゴリズムについてランダムにメモリを割当て
def alloc_random(alloclist, freelists, status, fitalgo, fitfunc):
    size = (random.randrange(maxsize // 10) + 1) * 10
    print('alloc ' + str(size))

    new_region = None
        
    for i in range(len(status)):
        if not status[i]:
            continue

        region = alloc(size, freelists[i], fitfunc[i])
        if region is None:
            status[i] = False
            print('cannot allocate: ' + fitalgo[i])
        else:
            new_region = region

        #print_range('freelist', freelists[i])

    if new_region is not None:
        alloclist.append(new_region)

    #print_range('alloclist', alloclist)

# ランダムにメモリを解放
def free_random(alloclist, freelists):
    items = len(alloclist)
    if items == 0:
        return

    index = random.randrange(items)
    region = alloclist[index]
    print('free ' + str(region.size))
    
    for i in range(len(status)):
        if status[i]:
            r = copy.copy(region)
            free(r, freelists[i])
            #print_range('freelist', freelists[i])
            
    alloclist.remove(region)
    #print_range('alloclist', alloclist)

fitalgo = []
fitfunc = []
freelists = []
status = []

alloclist = []

fitalgo.append('best-fit')
fitfunc.append(best_fit)
best_freelist = [ Region(0, memsize) ]
freelists.append(best_freelist)
status.append(True)

fitalgo.append('worst-fit')
fitfunc.append(worst_fit)
worst_freelist = [ Region(0, memsize) ]
freelists.append(worst_freelist)
status.append(True)

fitalgo.append('first-fit')
fitfunc.append(first_fit)
first_freelist = [ Region(0, memsize) ]
freelists.append(first_freelist)
status.append(True)

while True:
    action = random.randrange(3)
    if action == 1 or action == 2:
        alloc_random(alloclist, freelists, status, fitalgo, fitfunc)

        for i in range(len(status)):
            if status[i]:
                break
        else:
            break
    else:
        free_random(alloclist, freelists)

for i in range(len(status)):
    print_size(fitalgo[i] + ': free region', freelists[i])
