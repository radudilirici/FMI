data Binar  = Leaf Integer | Node Binar Binar deriving Show
type LeafCode = [Bool]

data Writer a = Writer { output ::[LeafCode], value :: a }

tree = Node (Node (Node (Leaf 3) (Leaf 4)) (Node (Leaf 1) (Leaf 4))) (Leaf 3)

leafCodesAux (Leaf lf) val = [[lf]]
leafCodesAux (Node n1 n2) val = (leafCodesAux n1 val) ++ (leafCodesAux n2 val)


-- leafCodes :: Binar -> Integer -> Writer ()
leafCodes (Leaf lf) val =
  if (lf == val) then [True]
  else [False]
-- leafCodes (Node n1 n2) val = leafCodes n1 val ++ leafCodes n2 val
