functia.de.la.pranz <- function(x)
{
  print("cartofi prajiti")
  x <- sqrt(x)
  sqrt(pi)
  return(x)
  return(sqrt(10))
}
functia.de.la.pranz(4) -> m

f2 <- function(r)
{
  pi*r^2
}
f2(1)
f2(1:20)

f3 <- function(x)
{
  3*x^2
}

integrate(f3, 0, 1) -> m
val <- m$value
#val <- m[[1]]
err <- m$abs.error

integrate(f3, 0, Inf)

t <- seq(0, 10, 0.001)
t1 <- seq(0, 10, length.out = 576)
plot(t, f3(t), col="#c0ffee")

f4 <- function(x)
{
  exp(-x^2/2)
}

integrate(f4, 0, Inf)
plot(t, f4(t), col="dark red", xlim=c(4, 6), ylim=c(0, 0.0005))

f5 <- function(x)
{
  1/(x+1)
}

integrate(f5, 0, Inf)
t <- seq(100, 1000, 0.01)
plot(t, f5(t), col="orange")
