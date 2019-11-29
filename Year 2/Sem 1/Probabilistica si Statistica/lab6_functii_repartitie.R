sample(1:5,6, replace = T)
par(mfrow = c(1,1))
set.seed(39)
x <- sample(0:2, 10000, replace = T, prob = c(1/2, 1/3, 1/6))
hist(x)
n0 <- length(x[x == 0])/10000
n1 <- length(x[x == 1])/10000
n2 <- length(x[x == 2])/10000

#repartitia Poisson

y <- rpois(10000, 10)
hist(y)

fm <- dpois(0:20, 10)
plot(0:20, dpois(0:20, 10), col = "darkred")

par(mfrow = c(1, 2))

t <- seq(-5, 25, 0.001)
#plot(t, ppois(t, 10), col = "darkgreen", ylim = c(0, 0.0005), xlim = c(-5, 3))
plot(t, ppois(t, 14), col = "darkblue")

fm[1]

t1 <- seq(-5, 5, 0.001)
plot(t1, pnorm(t1))
