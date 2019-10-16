d = {}
with open("F1.txt", "r") as fin:
    for word in next(fin).split():
        if word not in d.keys():
            d[word] = [1, 0]
        else:
            d[word][0] += 1
with open("F2.txt", "r") as fin:
    for word in next(fin).split():
        if (word) not in d.keys():
            d[word] = [0, 1]
        else:
            d[word][1] += 1

sus, st, dr = 0, 0, 0
for i in d.values():
    sus += i[0] * i[1]
    st += i[0] ** 2
    dr += i[1] ** 2
st = st ** 0.5
dr = dr ** 0.5

if st != 0 and dr != 0:
    cos = sus / (st * dr)
else:
    cos = 0
print(cos)