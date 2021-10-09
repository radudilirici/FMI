import Numeric.Natural

ordonataNat1 :: [Int] -> Bool
ordonataNat1 [] = True
ordonataNat1 [x] = True
ordonataNat1 (h1:h2:t) =
  if h1 <= h2 then ordonataNat1 (h2:t)
  else False

ordonata l rel = and [rel a b | (a, b) <- zip l (tail l)]

compuneList f l = [f . g | g <- l]

aplicaList a listF = [f a | f <- listF]

produsRec :: [Int] -> Int
produsRec [] = 1
produsRec (h:t) = h * produsRec t

produsFold :: [Int] -> Int
produsFold l = foldr (*) 1 l

andRec :: [Bool] -> Bool
andRec [] = True
andRec (h:t) = h && andRec t

andFoldr :: [Bool] -> Bool
andFoldr l = foldr (&&) True l

concatRec :: [[a]] -> [a]
concatRec [] = []
concatRec (h:t) = h ++ concatRec t

concatFoldr :: [[a]] -> [a]
concatFoldr l = foldr (++) [] l

rmChar :: Char -> String -> String
rmChar a xs = [x | x <- xs, x /= a]

rmCharsRec :: String -> String -> String
rmCharsRec [] s = s
rmCharsRec (h:t) s = rmCharsRec t (rmChar h s)

rmCharsFold :: String -> String -> String
rmCharsFold a l = foldr rmChar l a

logistic :: Num a => a -> a -> Natural -> a
logistic rate start = f
  where
    f 0 = start
    f n = rate * f (n - 1) * (1 - f (n - 1))

logistic0 :: Fractional a => Natural -> a
logistic0 = logistic 3.741 0.00079

ex1 :: Natural
ex1 = 20

ex20 :: Fractional a => [a]
ex20 = [1, logistic0 ex1, 3]

ex21 :: Fractional a => a
ex21 = head ex20

ex22 :: Fractional a => a
ex22 = ex20 !! 2

ex23 :: Fractional a => [a]
ex23 = drop 2 ex20

ex24 :: Fractional a => [a]
ex24 = tail ex20
