from math import sqrt


def dist(a, b):
    return sqrt((b[0] - a[0])**2 + (b[1] - a[1])**2)


def min_pct(x, y):
    if len(x) < 2:
        print(x, y)
        print("inf")
        return 999999999
    elif len(x) == 2:
        print(x, y)
        print(dist(x[0], x[1]))
        return dist(x[0], x[1])
    else:
        mijl = len(x) // 2
        ys = [a for a in y if a[0] < x[mijl][0]]
        yd = [a for a in y if a[0] >= x[mijl][0]]
        mins = min_pct(x[:mijl], ys)
        mind = min_pct(x[mijl:], yd)
        mn = min(mins, mind)
        lmin = x[mijl][0] - mn
        lmax = x[mijl][0] + mn
        ly = [a for a in y if a[0] >= lmin and a[0] <= lmax]
        nr_pct = len(ly)
        for i in range(nr_pct - 1):
            for j in range(i+1, min(i + 8, nr_pct)):
                aux = dist(ly[i], ly[j])
                if aux < mn:
                    mn = aux
        print(x, y)
        print(mn)
        return mn


if __name__ == '__main__':
    v = []
    with open("date.in", "r") as fin:
        n = int(next(fin))
        for i in range(n):
            aux = next(fin).split()
            x, y = float(aux[0]), float(aux[1])
            v.append((x, y))
    x = sorted(v)
    y = sorted(v, key=lambda a: a[1])
    print(min_pct(x, y))