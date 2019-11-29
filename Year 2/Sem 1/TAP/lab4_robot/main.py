with open("date.in", "r") as fin:
    aux = next(fin).split()
    n, m = int(aux[0]), int(aux[1])
    M = []
    for i in range(n):
        aux = [int(a) for a in next(fin).split()]
        M.append(aux)

prev = [["None" for a in range(m)] for b in range(n)]

for i in range(n):
    for j in range(m):
        if i == j == 0:
            continue
        if i == 0 or M[i][j - 1] > M[i - 1][j]:
            M[i][j] += M[i][j - 1]
            prev[i][j] = "st"
        else:
            M[i][j] += M[i - 1][j]
            prev[i][j] = "sus"


def afisare(i, j):
    if prev[i][j] == "sus":
        afisare(i - 1, j)
    elif prev[i][j] == "st":
        afisare(i, j - 1)
    print(i + 1, j + 1)


print(M[n - 1][m - 1])
afisare(n - 1, m - 1)