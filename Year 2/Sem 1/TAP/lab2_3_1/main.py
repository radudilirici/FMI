from random import choice


with open("date.in", "r") as fin:
    aux = next(fin).split()
    v = [int(a) for a in aux]

if len(v) % 2 != 0:
    print("Numar impar de valori!")
    exit()

def alege_val(parte, valori):
    """
    :param parte: "st" sau "dr"
    :param player: 1 sau 2
    :return: None
    """
    if len(valori) < 1:
        return
    val = 0
    if parte == "st":
        val = v[0]
        del v[0]
    elif parte == "dr":
        val = v[-1]
        del v[-1]
    return val


suma_impara = sum(b for a,b in enumerate(v, 1) if a % 2 == 1)
suma_para = sum(b for a,b in enumerate(v, 1) if a % 2 == 0)

if suma_impara >= suma_para:
    optiune = "st"
else:
    optiune = "dr"

suma_ai, suma_pc = 0, 0

aux = alege_val(optiune, v)
print(f"AI: {optiune}, valoarea {aux}")
suma_ai += aux

while len(v) > 2:
    optiune = choice(["st", "dr"])
    aux = alege_val(optiune, v)
    print(f"PC: {optiune}, valoarea {aux}")
    suma_pc += aux
    aux = alege_val(optiune, v)
    print(f"AI: {optiune}, valoarea {aux}")
    suma_ai += aux

aux = alege_val(optiune, v)
print(f"PC: {optiune}, valoarea {aux}")
suma_pc += aux

print(f"Suma AI: {suma_ai}\n"
      f"suma PC: {suma_pc}")
