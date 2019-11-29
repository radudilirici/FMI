from math import sqrt, acos, pi


def delta(p, q, r):
    return (q[0] * r[1] + p[0] * q[1] + r[0] * p[1]) - (q[0] * p[1] + r[0] * q[1] + r[1] * p[0])


def cos(a, b, c, d):
    ab = [b[0] - a[0], b[1] - a[1]]
    cd = [d[0] - c[0], d[1] - c[1]]
    sus = ab[0] * cd[0] + ab[1] * cd[1]
    jos = sqrt(ab[0] ** 2 + ab[1] ** 2) * sqrt(cd[0] ** 2 + cd[1] ** 2)
    if jos != 0:
        return sus / jos
    else:
        return 1


with open("date.in", "r") as fin:
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A1 = [x, y]
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A2 = [x, y]
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A3 = [x, y]
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A4 = [x, y]

d123 = delta(A1, A2, A3)
d234 = delta(A2, A3, A4)
d341 = delta(A3, A4, A1)
d412 = delta(A4, A1, A2)

if d123 * d234 > 0 and d234 * d341 > 0 and d341 * d412 > 0 and d412 * d123 > 0:
    print("Patrulaterul este convex")
else:
    print("Patrulaterul nu este convex")
    exit()

cosA2 = cos(A2, A1, A2, A3)
cosA4 = cos(A4, A1, A4, A3)

print(cosA2, cosA4)

degA2 = acos(cosA2)
degA4 = acos(cosA4)
deg = degA2 + degA4

if (deg - pi) ** 2 < 10 ** (-6):
    deg = 0
if deg == 0:
    print("A4 apartine cercului circumscris")
    exit()
elif deg < 0:
    print("A4 este in exteriorul cercului circumscris")  # invers?
    exit()
else:
    print("A4 este in interiorul cercului circumscris")  # invers?
