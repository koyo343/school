f = open('/proc/interrupts')

for line in f.readlines():
    line = line.strip()
    fields = line.split()

    if fields[0][:3] == "CPU":
        nr_cpus = len(fields)
        print('CPU0-{}'.format(nr_cpus-1).rjust(15))
        continue

    intr = sum(int(i) for i in fields[1:nr_cpus+1])
    
    print('{} {}  {}'.format(fields[0].rjust(4), str(intr).rjust(10),
                             ' '.join(fields[nr_cpus+1:])))
