import subprocess

chance = 0.05

l = [x*250 for x in range (1, 8)]
for vertices in l:
    out = 0
    for i in range(3):
        ret = subprocess.run(["./dijkstra", str(vertices), str(vertices/2), str(chance)], stdout = subprocess.PIPE)
        out += float(ret.stdout.decode('utf-8'))
    average = out/3
    print(str(vertices) + ' ' + str(average))

l = [x*500 for x in range (4, 10)]
for vertices in l:
    out = 0
    for i in range(3):
        ret = subprocess.run(["./dijkstra", str(vertices), str(vertices/2), str(chance)], stdout = subprocess.PIPE)
        out += float(ret.stdout.decode('utf-8'))
    average = out/3
    print(str(vertices) + ' ' + str(average))

l = [x*1000 for x in range (5, 10)]
for vertices in l:
    out = 0
    for i in range(3):
        ret = subprocess.run(["./dijkstra", str(vertices), str(vertices/2), str(chance)], stdout = subprocess.PIPE)
        out += float(ret.stdout.decode('utf-8'))
    average = out/3
    print(str(vertices) + ' ' + str(average))

l = [x*2500 for x in range (4, 11)]
for vertices in l:
    out = 0
    for i in range(3):
        ret = subprocess.run(["./dijkstra", str(vertices), str(vertices/2), str(chance)], stdout = subprocess.PIPE)
        out += float(ret.stdout.decode('utf-8'))
    average = out/3
    print(str(vertices) + ' ' + str(average))