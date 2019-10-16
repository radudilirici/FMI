#Comentariu
x <- 3
x <- c(-5:8, 1, 2, 3)
(y <- c(-543, 43, x, 22))
m1 <- cbind(x, y) -> m
rbind(x, y)
m[5,2]
z <- as.integer("4")
t <- c(1, "2", 3)
u <- -pi
v <- 1:100
v[(v%%5==0)&(v%%2!=0)] -> mama
cbind(x, y)
vector(length = 10)
numeric(3)
rep(c(1,2,3), each=3, 2)
rep(c(1,2,3), 1:3)
seq(1, 10, 0.7)
seq(0, 2*pi, length.out=20)
x[-c(1,3,5,7)]
x[x>1 & x<5]
sort(x)
A <- matrix(c(1,1,1,2,2,2,3,3,3), ncol=3, byrow = TRUE)
B <- matrix(c(1,0,0,0,1,0,0,0,1), ncol=3, byrow = TRUE)
A*B
A%*%B
a <- list(nume = "Vasile", varsta = 23, Salariat = T)
a[4] <- "ceva"
a[[5]] <- "altceva"
a[4] <- NULL
a[3] <- NULL
df <- data.frame("index" = 2:6,
                 "ceva1" = c(1, 3, 6, 1, 2),
                 "ceva2" = c(0.5, 0.7, 0.9, 0.2, 0.3))
rownames(df) <- df$index
df["ceva3"] <- c(1, 2, 2, 1, 2)
lst <- 5:9
rownames(df) <- lst
