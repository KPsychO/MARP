import subprocess
import time

f1 = open("./results_good_full", "w+")

f1.truncate(0)

l = [x*5 for x in range (1, 100)]
for v in l:
    out1 = 0
    for i in range(5):
        ret1 = subprocess.run(["./backpack", str(v), "1"], stdout = subprocess.PIPE)
        out1 += float(ret1.stdout.decode('utf-8'))
        time.sleep(0.5)

    goodaverage = out1/5
    print(str(v) + ' ' + str(goodaverage))
    f1.write(str(v) + ' ' + str(goodaverage) + '\n')

l = [x*10 for x in range (51, 100)]
for v in l:
    out = 0
    for i in range(15):
        ret1 = subprocess.run(["./backpack", str(v), "1"], stdout = subprocess.PIPE)
        out += float(ret1.stdout.decode('utf-8'))
        time.sleep(0.5)
        
    goodaverage = out/15
    print(str(v) + ' ' + str(goodaverage))
    f1.write(str(v) + ' ' + str(goodaverage) + '\n')


f1.close()