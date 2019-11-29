# mediana ponderata
# 7
# 5   1    3    2   9   6    11
# 0.1 0.12 0.05 0.1 0.2 0.13 0.3
# suma de wi = 1 (probabilitate)
# m mediana ponderata daca:
# (suma de wi, xi<m) < 0.5 si
# (suma de wi, xi>=m) <= 0.5
# in cazul asta: m = 6


def partitionare(v, st, dr):
    # print(st, dr)
    pivot = v[dr]
    i = st - 1
    for j in range(st, dr - 1):
        if v[j] <= pivot:
            i += 1
            v[i], v[j] = v[j], v[i]
            w[i], w[j] = w[j], w[i]
    i += 1
    v[i], v[dr] = v[dr], v[i]
    w[i], w[dr] = w[dr], w[i]
    return i


def mediana(v, w, st, dr, ws, wd):
    if st >= dr:
        return
    q = partitionare(v, st, dr - 1)
    auxs = auxd = 0
    for i in range(st, q):
        auxs += w[i]
    for i in range(q + 1, dr):
        auxd += w[i]
    auxs += ws
    auxd += wd
    # print(st, dr, q)
    # print(v)
    # print(ws, wd, auxs, auxd)
    # print(auxs < 0.5, auxd <= 0.5)
    # print()
    if auxs < 0.5 and auxd <= 0.5:
        return q
    if auxs >= 0.5 and auxd <= 0.5:
        auxd += w[q]
        return mediana(v, w, st, q, ws, auxd)
    if auxs < 0.5 and auxd > 0.5:
        auxs += w[q]
        return mediana(v, w, q + 1, dr, auxs, wd)
    return -1


if __name__ == '__main__':
    with open("date.in", "r") as fin:
        aux = next(fin).split()
        v = [int(a) for a in aux]
        aux = next(fin).split()
        w = [float(a) for a in aux]
    r = mediana(v, w, 0, len(v), 0, 0)
    if 0 <= r < len(v):
        print("poz:", r, "val:", v[r], "prob:", w[r])