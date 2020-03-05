def not_alpha(sir):
    v = []
    for s in sir:
        if not s.isalnum() and s != '-':
            v.append(s)
    return v


sir = input("Introduceti sirul ")

print(f'Lungime: {len(sir)}')

na = set(not_alpha(sir))
print(f'Nealfanumerice: {na}')

sir = sir.lower()
for a in na:
    sir = sir.replace(a, ' ')
cuvinte = sir.split()
print(f'Cuvinte: {cuvinte}')

masculine = []
for c in cuvinte:
    if len(c) >= 2:
        if c.endswith('ul'):
        # if c[-2:] == 'ul':
            masculine.append(c)
print(f'Cuv posibil masculine: {masculine}')

cratime = []
for c in cuvinte:
    if '-' in c:
        cratime.append(c)
print(f'Cratime: {cratime}')

