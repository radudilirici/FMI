from math import sqrt


def collinear(p0, p1, p2):
    x1, y1 = p1[0] - p0[0], p1[1] - p0[1]
    x2, y2 = p2[0] - p0[0], p2[1] - p0[1]
    return abs(x1 * y2 - x2 * y1) < 1e-12


def distanta(p1, p2):
    return sqrt(((p1[0] - p2[0]) ** 2) + ((p1[1] - p2[1]) ** 2))


def arie(p0, p1, p2):
    a = distanta(p0, p1)
    b = distanta(p0, p2)
    c = distanta(p1, p2)

    s = (a + b + c) / 2
    if (s * (s - a) * (s - b) * (s - c)) < 1e-3:
        return 0
    return round(sqrt(s * (s - a) * (s - b) * (s - c)), 2)


def delta(p, q, r):
    return (q[0] * r[1] + p[0] * q[1] + r[0] * p[1]) - (q[0] * p[1] + r[0] * q[1] + r[1] * p[0])


with open("date.in", "r") as fin:
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A1 = [x, y, 1]
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A2 = [x, y, 2]
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A3 = [x, y, 3]
    aux = next(fin).split()
    x, y = float(aux[0]), float(aux[1])
    A4 = [x, y, 4]

print(A1, A2, A3, A4)

if collinear(A1, A2, A3) and collinear(A1, A2, A4):
    if A1[0] != A2[0]:
        srted = sorted([A1, A2, A3, A4], key=lambda a: a[0])
        print(f"I = A{srted[0][2]}, A{srted[2][2]}")
        print(f"J = A{srted[1][2]}, A{srted[3][2]}")
    else:
        srted = sorted([A1, A2, A3, A4], key=lambda a: a[1])
        print(f"I = A{srted[0][2]}, A{srted[2][2]}")
        print(f"J = A{srted[1][2]}, A{srted[3][2]}")
    exit()

arie1 = [arie(A1, A2, A3), 1, 2, 3]
arie2 = [arie(A1, A2, A4), 1, 2, 4]
arie3 = [arie(A1, A3, A4), 1, 3, 4]
arie4 = [arie(A2, A3, A4), 2, 3, 4]

ariemax = max(arie1, arie2, arie3, arie3)
ariinotmax = [a[0] for a in [arie1, arie2, arie3, arie4] if a != ariemax]

if abs(sum(a for a in ariinotmax) - ariemax[0]) < 1e-5:
    print(f"I = A{ariemax[1]}, A{ariemax[2]}, A{ariemax[3]}")
    ultimul = 0
    for i in range(1, 5):
        if i not in ariemax[1:]:
            ultimul = i
            break
    if ultimul == 0:
        print("eroare")
        exit()
    print(f"J = A{ultimul}")
    exit()

d11 = delta(A1, A2, A3)
d12 = delta(A1, A2, A4)
d21 = delta(A1, A3, A2)
d22 = delta(A1, A3, A4)
d31 = delta(A1, A4, A2)
d32 = delta(A1, A4, A3)

print(d11, d12, d21, d22, d31, d32)

if d11 * d12 < 0:
    print("I = A1, A2")
    print("J = A3, A4")
elif d21 * d22 < 0:
    print("I = A1, A3")
    print("J = A2, A4")
elif d31 * d32 < 0:
    print("I = A1, A4")
    print("J = A2, A3")
else:
    print("Nu s-a gasit solutie...")

