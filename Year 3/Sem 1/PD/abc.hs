import Data.Char

-- data Pereche = P Int Int deriving Show
-- data Lista = L [Pereche] deriving Show
-- data Exp = I Int | Add Exp Exp | Mul Exp Exp
--
-- class ClassExp m where
--   toExp :: m -> Exp
--
-- instance ClassExp Lista where
--   toExp (L []) = I 0
--   toExp (L [(P x y)]) = Mul (I x) (I y)
--   toExp (L ((P x y):t)) = Add (Mul (I x) (I y)) (toExp (L t))
--
-- instance Show Exp where
--   show (I x) = show x
--   show (Add x y) = "(" ++ show x ++ "+" ++ show y ++ ")"
--   show (Mul x y) = "(" ++ show x ++ "*" ++ show y ++ ")"


data Pereche a b = MyP a b deriving Show
data ListaP a = MyL [a] deriving Show

class MyMapping m where
  mymap :: (Pereche a b -> Pereche b a) -> m (Pereche a b) -> m (Pereche b a)
  myfilter :: (Pereche a b -> Bool) -> m (Pereche a b) -> m (Pereche b a)

instance MyMapping ListaP where
  mymap _ (MyL []) = MyL []
  mymap transf (MyL (h:t)) = MyL ((transf h) : tf) where MyL tf = mymap transf (MyL t)
  -- myfilter _ (MyL []) = MyL []
  -- myfilter check (MyL (h:t))
  --   | (check h) = MyL (h:tf)
  --   | otherwise = MyL tf
  --   where
  --     MyL tf = myfilter check (MyL t)

elementAt1 :: [Int] -> [Int] -> Int -> Int
elementAt1 [] _ _ = 0
elementAt1 (h:t) (h2:t2) n
  | h2 == n = h
  | otherwise = elementAt1 t t2 n
elementAt :: [Int] -> Int -> Int
elementAt l n = elementAt1 l [1..] n
