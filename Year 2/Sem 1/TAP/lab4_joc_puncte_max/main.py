def print_d():
    for i in D:
        for j in i:
            # if isinstance(j, int):
            elem = '{: ^{width}}'.format(j, width=3)
            print(elem, end=" ")
            # else:
            #     print(j, end=" ")
        print()


with open("date.in", "r") as fin:
    aux = next(fin).split()
    v = [int(a) for a in aux]
n = len(v)
D = [[0 for i in range(n)] for j in range(n)]

print(n)
print(v)

for i in range(n):
    D[i][i] = v[i]
    if i + 1 < n:
        a = v[i]
        b = v[i + 1]
        if a > b:
            D[i][i + 1] = a
            D[i + 1][i] = 1
        else:
            D[i][i + 1] = b
            D[i + 1][i] = -1
# print()
# print_d()
# print()

for dim in range(2, n):
    for i in range(n - dim):
        j = i + dim
        a = v[i] + min(D[i + 1][j - 1], D[i + 2][j])
        b = v[j] + min(D[i + 1][j - 1], D[i][j - 2])
        if a > b:
            D[i][j] = a
            c = D[i + 1][j - 1]
            d = D[i + 2][j]
            if c < d:
                D[j][i] = 1
            else:
                D[j][i] = 2
        else:
            D[i][j] = b
            c = D[i + 1][j - 1]
            d = D[i][j - 2]
            if c < d:
                D[j][i] = -1
            else:
                D[j][i] = -2

print()
print_d()
print()

i, j = 0, n - 1
while i <= j - 1:
    directie = D[j][i]
    if directie == 2:
        print(f"AI:{v[i]} ({i}), PC:{v[i + 1]} ({i + 1})")
        i += 2
    elif directie == -2:
        print(f"AI:{v[j]} ({j}), PC:{v[j - 1]} ({j - 1})")
        j -= 2
    elif directie == 1:
        print(f"AI:{v[i]} ({i}), PC:{v[j]} ({j})")
        i += 1
        j -= 1
    else:
        print(f"AI:{v[j]} ({j}), PC:{v[i]} ({i})")
        i += 1
        j -= 1


