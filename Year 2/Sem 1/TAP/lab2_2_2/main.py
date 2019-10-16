with open("date.in", "r") as fin:
    n = int(next(fin))
    v = []
    for i in range(n):
        aux = next(fin).split()
        a, b = int(aux[0]), int(aux[1])
        v.append((a, b, i+1))

v.sort(key=lambda t: t[1], reverse=True)
for i in range(n):
    print(i+1, end=" ")
print()
for i in range(n):
    print(v[i][2], end=" ")
print()

timp_total = 0
for index, elem in enumerate(v):
    aux = elem[1] * sum(a[0] for a in v[:index + 1])
    timp_total += aux

print(timp_total)

# asd = [[], []]
# asd[0].append(1)
# asd[1].append(2)
# asd[1].append(3)
# print(asd)
#
# sdf = {}
# tup = (4, 5)
# vec = [7, 8, 9]
# a = "gjas"
# sdf[a] = vec
#
# print(sdf)