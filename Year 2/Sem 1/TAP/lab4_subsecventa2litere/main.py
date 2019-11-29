with open("date.in", "r") as fin:
    v = next(fin).split()
    print(v)

d = {}
ult = {}
pred = list(range(len(v)))
i = -1
mx = [0, 0]
for cuv in v:
    i += 1
    if cuv[0] in d:
        prima = d[cuv[0]]
    else:
        prima = 0
    if cuv[1] in d:
        ultima = d[cuv[1]]
    else:
        ultima = 0

    d[cuv[1]] = max(prima + 1, ultima)
    if d[cuv[1]] > mx[0]:
        mx[0] = d[cuv[1]]
        mx[1] = i
    if prima + 1 > ultima:
        if cuv[0] in ult:
            pred[i] = ult[cuv[0]]
        else:
            pred[i] = i
        ult[cuv[1]] = i

poz = mx[1]
print(mx[0])


def afisare(poz):
    if pred[poz] != poz:
        afisare(pred[poz])
    print(v[poz], end=" ")


afisare(poz)
