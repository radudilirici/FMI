# mediana a doi vectori sortati


def interclasare(v1, v2):
    i, j = 0, 0
    n1 = len(v1)
    n2 = len(v2)
    aux = []
    while i < n1 and j < n2:
        if v1[i] < v2[j]:
            aux.append(v1[i])
            i += 1
        else:
            aux.append(v2[j])
            j += 1
    while i < n1:
        aux.append(v1[i])
        i += 1
    while j < n2:
        aux.append(v2[j])
        j += 1
    return aux


def med(v1, v2):
    print(v1, v2)
    n1 = len(v1)
    n2 = len(v2)
    n = min(n1, n2)

    if len(v1) <= 2 or len(v2) <= 2:
        if len(v1) > len(v2):
            lung = v1
            scurt = v2
        else:
            lung = v2
            scurt = v1
        if len(scurt) == 1:
            x = scurt[0]
            if len(lung) % 2 == 0:
                mijl = len(lung) // 2 - 1
                if lung[mijl] < x < lung[mijl + 1]:
                    return x
                elif x < lung[mijl]:
                    return lung[mijl]
                else:
                    return lung[mijl + 1]
            else:
                mijl = len(lung) // 2
                if x < lung[mijl - 1]:
                    return (lung[mijl - 1] + lung[mijl]) / 2
                elif lung[mijl + 1] < x:
                    return (lung[mijl] + lung[mijl + 1]) / 2
                else:
                    return (x + lung[mijl]) / 2
        else:
            if len(lung) % 2 == 0:
                mijl = len(lung) // 2 - 1
                aux = lung[mijl:mijl+2]
            else:
                mijl = len(lung) // 2
                aux = lung[mijl - 1: mijl + 2]
            aux = interclasare(aux, scurt)
            print(aux)
            return (aux[len(aux) // 2] + aux[(len(aux) - 1) // 2]) / 2

        # aux = interclasare(v1, v2)
        # return (aux[(n1 + n2) // 2] + aux[(n1 + n2 - 1) // 2]) / 2

    m1 = (v1[n1 // 2] + v1[(n1 - 1) // 2]) / 2
    m2 = (v2[n2 // 2] + v2[(n2 - 1) // 2]) / 2
    to_remove = (n - 1) // 2
    if m1 == m2:
        return m1
    elif m1 < m2:
        return med(v1[to_remove:], v2[:-to_remove])
    else:
        return med(v1[:-to_remove], v2[to_remove:])


if __name__ == '__main__':
    with open("date.in", "r") as fin:
        next(fin)
        aux = next(fin).split()
        v1 = [int(a) for a in aux]
        next(fin)
        aux = next(fin).split()
        v2 = [int(a) for a in aux]
        print(med(v1, v2))
        print(sorted(v1+v2))
        print(f"len: {len(v1+v2)}")
