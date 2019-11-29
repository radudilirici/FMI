with open("date.in", "r") as fin:
    aux = next(fin).split()
    cost = [int(a) for a in aux]
    aux = next(fin).split()
    cuv1 = aux[0]
    cuv2 = aux[1]

n = len(cuv1)
m = len(cuv2)
M = [[0 for j in range(m)] for i in range(n)]
M[0] = [j for j in range(m)]

for i in range(1, n):
    M[i][0] = i
    for j in range(1, m):
        if cuv1[i] == cuv2[j]:
            M[i][j] = M[i - 1][j - 1]
        else:
            M[i][j] = min(M[i - 1][j - 1] + cost[2], M[i - 1][j] + cost[1], M[i][j - 1] + cost[0])

print(cuv1, cuv2)
for i in range(n):
    print(M[i])

edit = [None] * M[n - 1][m - 1]
i, j, k = n - 1, m - 1, M[n-1][m-1] - 1

while k >= 0 and i > 0 and j > 0:
    if cuv1[i] == cuv2[j]:
        i, j = i - 1, j - 1
    else:
        if M[i][j] == 1 + M[i - 1][j - 1]:
            edit[k] = "replace " + cuv1[i] + " - " + cuv2[j]
            i, j, k = i - 1, j - 1, k - 1
        elif M[i][j] == 1 + M[i - 1][j]:
            edit[k] = "delete " + cuv1[i]
            i, j = i - 1, k - 1
        elif M[i][j] == 1 + M[i][j - 1]:
            edit[k] = "add " + cuv2[j]
            j, k = j - 1, k - 1

while k >= 0 and i > 0:
    if M[i][j] == 1 + M[i - 1][j]:
        edit[k] = "delete " + cuv1[i]
        i, k, = i - 1, k - 1

while k >= 0 and j > 0:
    if M[i][j] == 1 + M[i][j - 1]:
        edit[k] = "add " + cuv2[j]
        j, k = j - 1, k - 1

for i in edit:
    print(i)