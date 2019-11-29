with open("date.in", "r") as fin:
    d = {}
    n = int(next(fin))
    for i in range(n):
        d[next(fin).split()[0]] = 1
with open("cod.in", "r") as fin:
    S = next(fin).split()[0]
n = len(S)
D = [0] * (n + 1)
D[n - 1] = 1
urm = [-1] * (n + 1)
urm[n - 1] = n

for i in range(n - 2, -1, -1):
    mn = D[i + 1]
    nxt = i + 1
    for j in range(i + 1, n + 1):
        currString = S[i:j]
        if currString in d:
            if D[j] < mn:
                mn = D[j]
                nxt = j
    D[i] = mn + 1
    urm[i] = nxt

print(D[0])

i = 0
while urm[i] != -1:
    print(S[i:urm[i]], end=" ")
    i = urm[i]
