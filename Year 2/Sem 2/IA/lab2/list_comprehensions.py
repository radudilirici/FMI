# 1
az = [chr(c) for c in range(ord('a'), ord('z') + 1)]
print(az)


# 2
def f2(n):
    return [(i + 1) * (-1)**i for i in range(n)]


print(f2(10))


# 9
def f9(str):
    return [str[i:] + str[:i] for i in range(len(str))]


print(f9('abcdefg'))


# 10
def f10(n):
    return [[i for j in range(i)]for i in range(n)]


print(f10(4))