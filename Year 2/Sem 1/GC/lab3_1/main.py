def getmatrixminor(m, i, j):
    return [row[:j] + row[j + 1:] for row in (m[:i] + m[i + 1:])]


def getmatrixdeternminant(m):
    if len(m) == 2:
        return m[0][0] * m[1][1] - m[0][1] * m[1][0]
    determinant = 0
    for c in range(len(m)):
        determinant += ((-1)**c) * m[0][c]*getmatrixdeternminant(getmatrixminor(m, 0, c))
    return determinant


class Punct:
    def __init__(self, a, b):
        self.x = a
        self.y = b


with open("date.in", "r") as fin:
    aux = [int(a) for a in next(fin).split()]
    A1 = Punct(aux[0], aux[1])
    aux = [int(a) for a in next(fin).split()]
    A2 = Punct(aux[0], aux[1])
    aux = [int(a) for a in next(fin).split()]
    A3 = Punct(aux[0], aux[1])
    aux = [int(a) for a in next(fin).split()]
    A4 = Punct(aux[0], aux[1])

line1 = line2 = [0, 0, 0]

if A1.x == A2.x:
    slope = "inf"
else:
    slope = (A2.y - A1.y)/(A2.x - A1.x)
if slope == "inf":
    line1 = [1, 0, -A1.x]
elif slope == 0:
    line1 = [0, 1, -A1.y]
else:
    line1 = [1, (-1) / slope, 1 / slope * A1.y - A1.x]

if A3.x == A4.x:
    slope = "inf"
else:
    slope = (A4.y - A3.y)/(A4.x - A3.x)
if slope == "inf":
    line2 = [1, 0, -A3.x]
elif slope == 0:
    line2 = [0, 1, -A4.y]
else:
    line2 = [1, (-1) / slope, 1 / slope * A3.y - A3.x]

print("ecuatiile liniilor:")
print(line1, line2)

delta = getmatrixdeternminant([[line1[0], line1[1]], [line2[0], line2[1]]])
print("delta:", delta)

if delta != 0:
    x = getmatrixdeternminant([[-line1[2], line1[1]], [-line2[2], line2[1]]]) / delta
    y = getmatrixdeternminant([[line1[0], -line1[2]], [line2[0], -line2[2]]]) / delta
    if (A1.x - x) * (A2.x - x) <= 0 and (A3.x - x) * (A4.x - x) <= 0 and (A1.y - y) * (A2.y - y) <= 0 and (A3.y - y) * (A4.y - y) <= 0:
        print("Segmentele se intersecteaza in:")
        print(x, y)
        exit()
    else:
        print("Punctul e in afara segmentelor (multimea vida)")
        exit()

det1 = getmatrixdeternminant([[line1[0], line1[2]], [line2[0], line2[2]]])
det2 = getmatrixdeternminant([[line1[1], line1[2]], [line2[1], line2[2]]])

if det1 != 0 or det2 != 0:
    print("Liniile sunt paralele si nu se intersecteaza (multimea vida)")
    exit()

# sunt coliniare
v = [[A1, 1], [A2, 2], [A3, 3], [A4, 4]]
if A1.x == A2.x:
    v.sort(key=lambda a: a[0].y)
else:
    v.sort(key=lambda a: a[0].x)

if v[1][0].x == v[2][0].x and v[1][0].y == v[2][0].y:
    print(f"Segmentele se intersecteaza in:")
    print(v[1][0].x, v[2][0].x)
    exit()
if {v[0][1], v[1][1]} == {1, 2} or {v[0][1], v[1][1]} == {3, 4}: # de modificat
    print("Punctele sunt coliniare si nu se intersecteaza (multimea vida)")
    exit()
print(f"Intersectia este segmentul: [A{v[1][1]} A{v[2][1]}]")

