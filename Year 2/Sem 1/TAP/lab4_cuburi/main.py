# n cuburi de dimensiuni diferite si culori diferite
# cum le punem unul peste altul daca avem voie sas punem doar mai mic pe mai mare
# si sa nu fie aceeasi culoare la 2 cuburi consecutive (vrem inaltime maxima)

with open("date.in", "r") as fin:
    n = int(next(fin))
    H = [0] * n
    succ = [-1] * n
    NR = [1] * n
    v = []
    for i in range(n):
        aux = [int(a) for a in next(fin).split()]
        v.append(tuple(aux))
v.sort(key=lambda x: x[0] * 10 + x[1], reverse=True)

for i in range(n - 1, -1, -1):
    H[i] = v[i][0]
    mx = H[i]
    nraux = NR[i]
    for j in range(i + 1, n):
        if v[j][0] < v[i][0] and v[j][1] != v[i][1]:
            if H[j] + H[i] > mx:
                mx = H[j] + H[i]
                succ[i] = j
                nraux = NR[j]
            elif H[j] + H[i] == mx:
                nraux += NR[j]
    H[i] = mx
    NR[i] = nraux

mxidx = 0
nrpos = NR[mxidx]
for i in range(1, n):
    if H[i] > H[mxidx]:
        mxidx = i
        nrpos = NR[i]
    elif H[i] == H[mxidx]:
        nrpos += NR[i]

print(H)
print(succ)
print(NR)

while True:
    print(v[mxidx], end=" ")
    if succ[mxidx] == -1:
        break
    mxidx = succ[mxidx]

print()
print(nrpos)