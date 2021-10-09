import Data.Char (toUpper)

prelStr strin = map toUpper strin

ioString = do
            strin <- getLine
            putStrLn $ "Intrare\n" ++ strin
            let  strout = prelStr strin
            putStrLn $ "Iesire"
            putStrLn strout


prelNo noin =  sqrt noin
ioNumber = do
            noin  <- readLn :: IO Double
            putStrLn $ "Intrare\n" ++ (show noin)
            let  noout = prelNo noin
            putStrLn $ "Iesire"
            print noout



inoutFile = do
               sin <- readFile "Input.txt"
               putStrLn $ "Intrare\n" ++ sin
               let sout = prelStr sin
               putStrLn $ "Iesire\n" ++ sout
               writeFile "Output.txt" sout
