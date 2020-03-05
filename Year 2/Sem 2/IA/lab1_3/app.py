sir = input('Introduceti stinngul ')
cuv = input('Introduceti cuvantul ')
cuv = set([c for c in cuv])

sir = sir.split()
sir = [x.strip(',.!?"') for x in sir]

v = []

for s in sir:
    sset = set([_ for _ in s])
    if cuv.issubset(sset) and cuv.issuperset(sset):
        v.append(s)

print(v)