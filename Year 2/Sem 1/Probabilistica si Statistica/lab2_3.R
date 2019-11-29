agg_mean <- aggregate(iris[, 1:4], by=list(iris$Species), FUN=mean)
agg_max <- aggregate(iris[, 1:4], by=list(iris$Species), FUN=max)
frm <- y ~ x1 * x2
x <- paste0("x", 1:25)
frm <- as.formula(paste("y ~ ", paste(x, collapse = " + ")))
agg <- aggregate(iris[, 1:4], abc ~ Sepal.Lenght + Sepal.Width, mean)
hist(x = iris$Sepal.Length[iris$Species == "setosa"], main = "Sepal Lenghts", xlab = "Lenght", ylab = "Frequency", xlim = c(4, 8.5), breaks = length(iris$Species[iris$Species == "setosa"]) / 3, col = "light blue")
hist(x = iris$Sepal.Length[iris$Species == "versicolor"], xlim = c(4, 8.5), breaks = length(iris$Species[iris$Species == "versicolor"]) / 2, add = T, col = "orange")
hist(x = iris$Sepal.Length[iris$Species == "virginica"], xlim = c(4, 8.5), breaks = length(iris$Species[iris$Species == "virginica"]) / 2, add = T, col = "dark red")