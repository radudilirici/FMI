# 8. S˘a se genereze variabila Gama(0.5, 2, 0.25) folosind teorema ˆınf˘a¸sur˘atoarei
# (curs 3). S˘a se genereze variabila Poisson prin dou˘a metode (curs 7).

# %%
%pylab inline

def medie(distributie):
  return np.sum(distributie) / len(distributie)

def dispersie(distributie):
  m = medie(distributie) ** 2
  distributie_2 = []
  for x in distributie:
    distributie_2.append(x ** 2)
  return (np.sum(distributie_2) / len(distributie)) - m

# %%
### Variabila Gama

def genGamma(alpha, lam, v):
    c = 1 / v

    while True:
        U = np.random.uniform(0, 1)
        Y = int( (-1) * np.log(U) ) ** c
        U = np.random.uniform(0, 1)

        if U <= alpha * np.exp(Y ** v - Y):
            break
    
    return alpha + (Y / lam)


alpha = 0.5
lam = 2
v = 0.25

N = 50000
X = np.array( [genGamma(alpha, lam, v) for _ in range(N)] )
plt.hist(X)
plt.show()

medie_t = alpha + v / lam
dispersie_t = v / (lam ** 2)

medie_e = medie(X)
dispersie_e = dispersie(X)

print(f'Media si dispersia teoretice sunt: {medie_t, dispersie_e}.')
print(f'Media si dispersia empirice sunt: {medie_e, dispersie_e}.')
print(f'Diferentele sunt: {abs(medie_t - medie_e), abs(dispersie_e - dispersie_e)}.')





# %%
### Repartitia Poisson

def genPoisson1(lam):
    i = 0
    P = 1

    while True:
        U = np.random.uniform(0, 1)
        i += 1
        P *= U

        if P < np.exp(-lam):
            break
    
    return i - 1

def genPoisson2(lam):
    p = 0.0001
    n = round(lam / p)
    return np.random.binomial(n, p)

lam = 2

N = 20000
X = np.array([genPoisson1(lam) for _ in range(N)])
plt.hist(X)
plt.show()

medie_e = medie(X)
dispersie_e = dispersie(X)

print(f'Media si dispersia teoretice sunt: {lam, lam}.')
print(f'Media si dispersia empirice 1 sunt: {medie_e, dispersie_e}.')
print(f'Diferentele 1 sunt: {abs(lam - medie_e), abs(lam - dispersie_e)}.')


X = np.array([genPoisson1(lam) for _ in range(N)])
plt.hist(X)
plt.show()

medie_e = medie(X)
dispersie_e = dispersie(X)

print(f'Media si dispersia teoretice sunt: {lam, lam}.')
print(f'Media si dispersia empirice 2 sunt: {medie_e, dispersie_e}.')
print(f'Diferentele 2 sunt: {abs(lam - medie_e), abs(lam - dispersie_e)}.')
    

# %%
