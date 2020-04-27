import subprocess

f1 = open("./results_good", "w+")
f2 = open("./results_bad", "w+")

f1.truncate(0)
f2.truncate(0)

l = [x for x in range (5, 21)]
for v in l:
    out1 = 0
    out2 = 0
    for i in range(10):
        ret1 = subprocess.run(["./backpack", str(v), "1"], stdout = subprocess.PIPE)
        ret2 = subprocess.run(["./backpack", str(v), "2"], stdout = subprocess.PIPE)
        out1 += float(ret1.stdout.decode('utf-8'))
        out2 += float(ret2.stdout.decode('utf-8'))
    goodaverage = out1/10
    badaverage = out2/10
    print(str(v) + ' ' + str(goodaverage))
    f1.write(str(v) + ' ' + str(goodaverage) + '\n')
    print(str(v) + ' ' + str(badaverage))
    f2.write(str(v) + ' ' + str(badaverage) + '\n')


f1.close()
f2.close()