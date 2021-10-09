import Data.Char

-- f :: Int -> [Char] -> [Char]
-- f 0 l = []
-- f n [] = error "n e prea mare"
-- f n (h:t) = h : f (n-1) t
-- g :: Int -> [Char] -> [Char]
-- g 0 l = l
-- g n [] = error "n e prea mare"
-- g n (h:t) = g (n-1) t
rotate :: Int -> [Char] -> [Char]
-- rotate n l = g n l ++ f n l
rotate n str
  | n > 0 && n < length str = str2 ++ str1
  | otherwise = error "N este invalid"
  where
  str1 = take n str
  str2 = drop n str

makeKey :: Int -> [(Char, Char)]
makeKey n = zip alph (rotate n alph)
  where alph = ['A' .. 'Z']

lookUp :: Char -> [(Char, Char)] -> Char
lookUp c [] = c
lookUp c ((a,b):t) =
  if a == c then b
  else lookUp c t

encipher :: Int -> Char -> Char
encipher n c = lookUp c (makeKey n)

normalize :: String -> String
-- normalize l = [toUpper c | c <- l, not(isPunctuation c), not(isSeparator c)]
normalize s = filter (`elem` (['A' .. 'Z'] ++ ['0' .. '9'])) [toUpper c | c <- s]

encipherStr :: Int -> String -> String
encipherStr n l = [encipher n c | c <- normalize l]

reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey [] = []
reverseKey ((a, b):t) = (b, a) : reverseKey t

decipher :: Int -> Char -> Char
decipher n c = lookUp c $reverseKey $makeKey n

decipherStr :: Int -> String -> String
decipherStr n l = [decipher n c | c <- l]
