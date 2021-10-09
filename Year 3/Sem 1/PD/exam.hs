-- diviz_ [x] n = n mod x == 0
-- diviz_ [h:t] n =
--   if n mod h == 0 then diviz t n
--   else False
--
-- diviz n = diviz_ [1..n/2] n

divisors :: Int -> [Int]
divisors k = (1:divisors' 2 k)
  where
    divisors' n k | n*n > k = [k ^ 2]
                  | n*n == k = [n, k ^ 2]
                  | k `mod` n == 0 = (n ^ 2:(k `div` n) ^ 2:result)
                  | otherwise = result
      where result = divisors' (n+1) k



sterge :: String -> String -> String
sterge s1 s2 = filter (not.(`elem` s1)) s2


-- data Expr a = Const a | Sum (Expr a) (Expr a) | Mul (Expr a) (Expr a)

-- instance Show (Expr a) where
--   show (Const a) = show(a)
--   show (Sum x y) = "("++show(x)++" + "++show(y)++")"
--   show (Mul x y) = "("++show(x)++" * "++show(y)++")"

-- Class MapClass f where
-- myMap :: (a->b) -> f a -> f b
-- myMap f (Const a) = Const (f a)

-- instance MapClass f  where
--   myMap f (MyL pereche) = MyL [ f(MyP a b)|(MyP a b) <- pereche]
-- a) Sa se scrie o instanta a clasei MapClass astfel incat functia myMap sa functioneze la fel ca map (pe liste), aplicand functia data pe parametru pe fiecare element de tip a din expresie, transformand Const a in Const b.
-- b) Sa se scrie o instanta a clasei Show astfel incat sa se faca afisarea cu + si * in loc de constructori. ~
