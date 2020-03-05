str1 = input("Introduceti stringul 1 ")
str1 = [a for a in str1]
str2 = input("Introduceti stringul 2 ")
str2 = [a for a in str2]

print(str1)
print(str2)

for c in str1:
    if c in str2:
        str2.remove(c)

if len(str2) == 0:
    print('Sunt anagrame')
else:
    print('Nu sunt anagrame')