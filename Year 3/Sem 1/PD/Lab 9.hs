import Data.Char (toUpper)
-- import Data.List.Split

-- Exemplu 1
prelStr strin = map toUpper strin

ioString = do
  strin <- getLine
  putStrLn $ "Intrare\n" ++ strin
  let  strout = prelStr strin
  putStrLn $ "Iesire"
  putStrLn strout

-- Exemplu 2
prelNo noin = sqrt noin

ioNumber = do
  noin <- readLn :: IO Double
  putStrLn $ "Intrare\n" ++ (show noin)
  let  noout = prelNo noin
  putStrLn $ "Iesire\n" ++ (show noout)

-- Exemplu 3
inoutFile = do
  sin <- readFile "Laborator 9/Input.txt"
  putStrLn $ "Intrare\n" ++ sin
  let sout = prelStr sin
  putStrLn $ "Iesire\n" ++ sout
  writeFile "Output.txt" sout

-- 1
ex1aux :: Int -> Int -> String -> IO()
ex1aux 0 mx raspuns = do
  putStrLn $ raspuns ++ " " ++ (show mx) ++ " ani."
ex1aux n mx raspuns = do
  nume <- readLn :: IO String
  varsta <- readLn :: IO Int
  if varsta == mx then
    ex1aux (n-1) mx (raspuns ++ ", " ++ nume)
  else
    if varsta > mx then
      ex1aux (n-1) varsta nume
    else
      ex1aux (n-1) mx raspuns

ex1 = do
  n <- readLn :: IO Int
  ex1aux n 0 ""

-- 2
mySplit :: Char -> String -> String -> [String]
mySplit sep "" s = [s]
mySplit sep (c:cs) s
   | c == sep = [s] ++ mySplit sep cs ""
   | otherwise = mySplit sep cs (s ++ [c])


-- 3
invers "" = ""
invers (h:t) = invers t ++ [h]

verif n =
  if nstr == invers nstr then do
    putStrLn $ nstr ++ " este palindrom."
  else
    putStrLn $ nstr ++ " nu este palindrom."
  where
      nstr = (show n)

verifn_aux 0 = return ()
verifn_aux nr = do
  n <- readLn :: IO Int
  verif n
  verifn_aux (nr - 1)

verifn = do
  n <- readLn :: IO Int
  verifn_aux n
