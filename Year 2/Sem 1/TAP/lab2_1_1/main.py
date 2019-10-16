with open("date.in", "r") as fin:
    aux = next(fin).split()
    A, B = int(aux[0]), int(aux[1])
    n = int(next(fin))
    v = []
    for i in range(n):
        aux = next(fin).split()
        v.append((int(aux[0]), int(aux[1])))

v.sort()
print(v)

if A < v[0][0]:
    print(-1)
    exit()

nr, mx = 0, 0
intervale = []
intervalaux = []

for i in v:
    if i[0] > A:
        if i[0] > mx:
            print(-1)
            exit()
        A = mx
        nr += 1
        intervale.append(intervalaux)
        if A >= B:
            break
    if i[1] > mx:
        mx = i[1]
        intervalaux = i

if A < B and mx > B:
    nr += 1
    intervale.append(intervalaux)

print(nr)
print(intervale)

with open("date.out", "w") as fout:
    fout.write(str(nr))