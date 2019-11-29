

with open("date.in", "r") as fin:
    v = [int(a) for a in next(fin).split()]
    n = len(v)
    HCresc = [0] * n
    HDesc = [0] * n
    succCresc = [-1] * n
    succDesc = [-1] * n

for i in range(n - 1, -1, -1):
    HDesc[i] = 1
    mx = HDesc[i]
    for j in range(i + 1, n):
        if v[j] < v[i]:
            if HDesc[j] + HDesc[i] > mx:
                mx = HDesc[j] + HDesc[i]
                succDesc[i] = j
    HDesc[i] = mx

for i in range(0, n):
    HCresc[i] = 1
    mx = HCresc[i]
    for j in range(i):
        if v[j] < v[i]:
            if HCresc[j] + HCresc[i] > mx:
                mx = HCresc[j] + HCresc[i]
                succCresc[i] = j
    HCresc[i] = mx

print(HDesc)
print(HCresc)

raspuns = [0, 0]
for i in range(n):
    aux = HCresc[i] + HDesc[i]
    if HCresc[i] > 1 and HDesc[i] > 1 and aux > raspuns[0]:
        raspuns[0] = aux
        raspuns[1] = i
poz = raspuns[1]

def print_stanga(poz):
    if succCresc[poz] != -1:
        print_stanga(succCresc[poz])
    print(v[poz], end=" ")


print_stanga(poz)
poz = succDesc[poz]
while True:
    if poz == -1:
        break
    print(v[poz], end=" ")
    poz = succDesc[poz]
print()