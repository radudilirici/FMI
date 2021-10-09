-- 1
import Data.Char

suma_cod :: [Char] -> Int
suma_cod [] = 0
suma_cod (h:t) =
  if (h == 'a' || h == 'e' || h == 'i' || h == 'o' || h == 'u' || h == 'A' || h == 'E' || h == 'I' || h == 'O' || h == 'U' ) then suma_cod t
  else if isAlpha h then 1 + suma_cod t
  else if isDigit h then 2 + suma_cod t
  else suma_cod t - 1

-- 2
prod_sum :: [[Int]] -> Int
prod_sum m = foldr (*) 1 (map f m)
  where
    f v = foldr (+) 0 (filter even v)

-- 3
data MyPair a b = P a b deriving Show
data MyList a = L [a] deriving  Show

class MyZip lp where
  zipL :: lp a -> lp b -> lp (MyPair  a b)
  unzipL ::  lp (MyPair  a b) -> MyPair (lp a) (lp b)

instance MyZip MyList where
  zipL (L []) _ = L []
  zipL _ (L []) = L []
  zipL (L l1) (L l2) = L (zipAux l1 l2)
    where
      zipAux :: [a] -> [b] -> [MyPair a b]
      zipAux [] _ = []
      zipAux _ [] = []
      zipAux (h1:t1) (h2:t2) = [P h1 h2] ++ zipAux t1 t2
  unzipL (L []) = P (L[]) (L[])
  unzipL (L (P a b:t)) = myAdd a b (unzipL (L t))
    where
      myAdd :: a -> b -> MyPair (MyList a) (MyList b) -> MyPair (MyList a) (MyList b)
      myAdd a b (P (L l1) (L l2)) = P (L (a:l1) ) (L (b:l2) )
