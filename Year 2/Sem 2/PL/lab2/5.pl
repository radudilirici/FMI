scalarMult(_, [], []).
scalarMult(N, [Elem | Tail], [Elem2 | Result]) :- scalarMult(N, Tail, Result),
												  Elem2 is Elem * N.

dot([], [], 0).
dot([Elem1 | Tail1], [Elem2 | Tail2], Result) :- dot(Tail1, Tail2, Result2),
												 Result3 is Elem1 * Elem2,
												 Result is Result2 + Result3 .