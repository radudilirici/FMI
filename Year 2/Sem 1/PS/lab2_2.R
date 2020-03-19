aux <- function(a) #functia gamma
{
  aux2 <- function(x)
  {
    x^(a-1)*exp(-x)
  }
  integrate(aux2, 0, Inf)
}
aux(1/2)
sqrt(pi)

#sol2-luiza
F1 <- function(x, a)
{
  x^(a-1)*exp(-x)
}
integrate(F1, 0, Inf, 5) #a este parametru si il precizam aici

gamma(1/3)


my.gamma <- function(a)
{
  if (a <= 0)
    return(-1)
  else if (all.equal(a, 1) == T)
    return(1)
  else if (all.equal(a, 1/2) == T)
    return (pi/2)
  else if (all.equal(a, floor(a)) == T)
    return(factorial(a-1))
  aux3 <- function(x)
  {
    x^(a-1)*exp(-x)
  }
  aux.var <- integrate(aux3, 0, Inf)
  return(aux.var$val)
}
my.gamma(13/3)
gamma(13/3)