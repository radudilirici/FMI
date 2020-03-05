# 2
print('Ex 2')


v2 = [213, 4, 34, -1, 9, 333, 0]
print(sorted(v2, key=lambda x: str(x)))
print(sorted(v2, key=lambda x: str(x)[::-1]))
print(sorted(v2, key=lambda x: len(str(x))))
print(sorted(v2, key=lambda x: len(set(str(x)))))
print()


# 3
print('Ex 3')


def gen_matrice():
    v = [[0] + [chr(c) for c in range(ord('a'), ord('z') + 1)]]
    for i in range(ord('a'), ord('z') + 1):
        v.append([chr(i)] + [0] * (ord('z') - ord('a') + 1))
    return v


mat = gen_matrice()


def completeaza_matrice(cuvinte, matrice):
    for cuvant in cuvinte:
        for i in range(len(cuvant) - 1):
            y = ord(cuvant[i]) - ord('a') + 1
            x = ord(cuvant[i + 1]) - ord('a') + 1
            matrice[y][x] += 1


completeaza_matrice(["papagal", "pisica","soarece","bolovan","soparla","catel", "pasare"], mat)


def curatare_matrice(matrice):
    for i in range(len(matrice) - 1, 0, -1):
        all0 = True
        for j in range(1, len(matrice[i])):
            if matrice[i][j] != 0:
                all0 = False
        if all0:
            matrice.pop(i)
    for j in range(len(matrice[0]) - 1, 0, -1):
        all0 = True
        for i in range(1, len(matrice)):
            if matrice[i][j] != 0:
                all0 = False
        if all0:
            for i in range(len(matrice)):
                matrice[i].pop(j)


curatare_matrice(mat)

for l in mat:
    print(l)
print()


def aparitii_matrice(matrice, N):
    aparitii = []
    for i in range(1, len(matrice)):
        for j in range(1, len(matrice[i])):
            if matrice[i][j] >= N:
                aparitii.append(matrice[i][0] + matrice[0] [j])
    return aparitii


print(aparitii_matrice(mat, 2))
print()


# 4
print('Ex 4')


v4 = ["haha", "poc", "Poc", "POC", "haHA", "hei", "hey", "HahA", "poc", "Hei"]
v4 = [s.lower() for s in v4]
d4 = {}
for e in v4:
    if e in d4:
        d4[e] += 1
    else:
        d4[e] = 1
print(d4)
print()


# 5
print('Ex 5')


lungimi = {(1, 4): 'mic', (4, 8): 'mediu', (8, 15): 'mare'}
cuvinte = ["bau-bau", "bobocel", "14 pisici", "1pitic", "pisicel", "botosel", "414", "ham", "-hau", "bob", "bocceluta"]
caractere = set()
for cuvant in cuvinte:
    for caracter in cuvant:
        caractere.add(caracter)

dictionar = {}
for caracter in caractere:
    v = []
    for cuv in cuvinte:
        if caracter in cuv:
            v.append(cuv)
    if len(v):
        dictionar[caracter] = v

print(dictionar)

toDel = []
for k in dictionar.keys():
    if not k.isalnum():
        toDel.append(k)
print(f'Chei non alfanumerice: {toDel}')
for td in toDel:
    del dictionar[td]

print(dictionar)
print(f'Au mai ramas {len(dictionar)} chei')
print()

for (key, val) in dictionar.items():
    tipuri = set()
    for cuv in val:
        for (lung, tip) in lungimi.items():
            if lung[0] <= len(cuv) < lung[1]:
                tipuri.add(tip)
    print(key, tipuri)

print()

# 6
print('Ex 6')


def gen_mat(n):
    return [[i + j for j in range(n)] for i in range(n)]


aux = gen_mat(4)
for l in aux:
    print(l)
print()


def gen_mat2(l1, l2):
    return [['>' if l1[i] > l2[j] else '==' if l1[i] == l2[j] else '<' for j in range(len(l2))] for i in range(len(l1))]


aux = gen_mat2([1, 5, 6], [8, 5, 2])
for l in aux:
    print(l)
