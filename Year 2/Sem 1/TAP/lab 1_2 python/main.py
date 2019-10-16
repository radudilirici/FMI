d = {}
with open("date.in", "r") as fin:
    n = int(next(fin))
    for l in range(n):
        v = [int(x) for x in next(fin).split()]
        for i in range(3):
            key = tuple(sorted(v[:i] + v[i + 1:]))
            if key not in d:
                d[key] = [v[i], 0]
            else:
                mx = max(d[key])
                d[key] = [v[i], mx]

raza_max = 0
for i in d.items():
    raza_crt = min(min(i[0]), sum(i[1])) / 2
    raza_max = max(raza_crt, raza_max)

print(raza_max)