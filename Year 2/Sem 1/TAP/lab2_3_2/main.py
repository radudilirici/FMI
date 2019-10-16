def df(x, add, lst, I):
    add[x] = 1
    if lst[x] != None:
        for y in lst[x]:
            df(y, add, lst, I)
            if add[y] == 1:
                add[x] = 0
    if add[x] == 1:
        I.append(x)


with open("date.in", "r") as fin:
    aux = next(fin).split()
    n, m = int(aux[0]), int(aux[1])
    if m != n-1:
        print("date incorecte")
        exit()
    lst = (n+1) * [None]
    for i in range(m):
        aux = next(fin).split()
        a, b = int(aux[0]), int(aux[1])
        if lst[a] == None:
            lst[a] = [b]
        else:
            lst[a].append(b)

I = []
add = list(range(n+1))
df(1, add, lst, I)
print(add)
print(lst)
print(I)