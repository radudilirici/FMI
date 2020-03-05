aux = input("Introduceti sirul de numere ").split()
v = [int(a) for a in aux]

max1, max2 = '', ''

for i in v:
    if max2 == '':
        max1 = max2
        max2 = i
    elif i > max2:
        max1 = max2
        max2 = i
    elif max1 == '' and i < max2:
        max1 = i
    elif max2 > i > max1:
        max1 = i

if max1 == '' or max2 == '':
    print('Imposibil')
else:
    print(max1, max2)