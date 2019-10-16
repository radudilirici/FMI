# Sortam descrescator dupa p
# Parcurgem activitatile si le punem pe timpul maxim

with open("date.in", "r") as fin:
    n = int(next(fin))
    v = []
    for i in range(n):
        aux = next(fin).split()
        v.append((int(aux[0]), int(aux[1]), i + 1))

v = sorted(v, key=lambda tup:tup[0], reverse=True)
print(v)

program = (n+1) * [0]
for i in range(len(program)):
    program[i] = [0, 0]

sum = 0
for i in v:
    tmax = i[1]
    while program[tmax][0] == 1 and tmax != 0:
        tmax -= 1
    if tmax != 0:
        program[tmax][0] = 1
        program[tmax][1] = i[2]
        sum += i[0]

print(program)
print()

print(sum)
print([a[1] for a in program if a[0] == 1])

with open("date.out", "w") as fout:
    fout.write(str(sum))
    fout.write("\n")
    fout.write(str([a[1] for a in program if a[0] == 1]))