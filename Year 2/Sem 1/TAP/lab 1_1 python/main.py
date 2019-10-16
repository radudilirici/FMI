with open("date.in", "r") as fin:
    next(fin)
    numbers_str = next(fin)
    v = [int(x) for x in numbers_str.split()]

v = sorted(v)

i = 0
while i < len(v):
    j, k = i + 1, len(v) - 1
    while j < k:
        suma = v[i] + v[j] + v[k]
        if suma < 0:
            while v[j] == v[j + 1]:
                j += 1
            j += 1
        elif suma > 0:
            while v[k] == v[k - 1]:
                k -= 1
            k -= 1
        else:
            print(v[i], v[j], v[k])
            while v[j] == v[j + 1]:
                j += 1
            j += 1
            while v[k] == v[k - 1]:
                k -= 1
            k -= 1

    while i + 1 < len(v):
        if v[i] == v[i + 1]:
            i += 1
        else:
            break
    i += 1



