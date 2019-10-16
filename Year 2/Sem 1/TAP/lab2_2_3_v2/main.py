# Cu Kruskal
# Union Find

with open("date.in", "r") as fin:
    n = int(next(fin))
    v = []
    for i in range(n):
        aux = next(fin).split()
        v.append((int(aux[0]), int(aux[1]), i + 1))
        if v[-1][1] > n:
            v[-1][1] = n

v = sorted(v, reverse=True)
print(v, "\n")

t = aux = list(range(n+1))
aux = [i - 1 for i in aux]
rank = (n+1) * [0]
# print(t)
# print(aux)
# print(rank)
# print()


def find(x):
    if t[x] == x:
        return x
    return find(t[x])


def union(x, y):
    xroot = find(x)
    yroot = find(y)
    if rank[xroot] < rank[yroot]:
        t[xroot] = yroot
        aux[yroot] = min(aux[xroot], aux[yroot])
    elif rank[xroot] > rank[yroot]:
        t[yroot] = xroot
        aux[xroot] = min(aux[xroot], aux[yroot])
    else:
        t[yroot] = xroot
        rank[xroot] += 1
        aux[xroot] = min(aux[xroot], aux[yroot])


sum = 0
selectate = []
for i in v:
    tata = find(i[1])
    a = aux[tata]
    # print(f, a)
    if a >= 0:
        union(a, i[1])
        sum += i[0]
        selectate.append(i[2])

# print()
# print(t)
# print(aux)
# print(rank)
# print()
print(sum)
print(selectate)
