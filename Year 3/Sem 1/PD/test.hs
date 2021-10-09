sfChrAux :: Char -> [Char] -> Bool
sfChrAux c [] = False
sfChrAux c (h:t) = c == h || sfChrAux c t

sfChr :: Char -> Bool
sfChr c = sfChrAux c ".!?:"

nrProp :: [Char] -> Int
nrProp [] = 0
nrProp (h:t)
  | sfChr h = 1 + nrProp t
  | otherwise =  nrProp t

liniiN :: [[Int]] -> Int -> Bool
liniiN m n = m2 == filter f m2
  where
    m2 = filter (\x -> length x == n) m
    f x = filter g x == x
    g x = x >= 0

data Punct = Pt [Int]
  deriving Show

data Arb = Vid | F Int | N Arb Arb
  deriving Show

class ToFromArb a where
  toArb :: a -> Arb
  fromArb :: Arb -> a

instance ToFromArb Punct where
  toArb (Pt []) = Vid
  toArb (Pt (h:t)) = N (F h) (toArb (Pt t))
  fromArb Vid = Pt []
  fromArb (F e) = Pt [e]
  fromArb (N a1 a2) = addPt (fromArb a1) (fromArb a2)
    where
      addPt :: Punct -> Punct -> Punct
      addPt (Pt l1) (Pt l2) = Pt (l1 ++ l2)
