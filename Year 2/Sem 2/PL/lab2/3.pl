line(0, _):- nl.
line(N, C) :- write(C),
			  N1 is N - 1,
			  line(N1, C).

square_aux(_, 0, _).
square_aux(N, N2, C) :- line(N, C),
						N3 is N2 - 1,
						square_aux(N, N3, C).

square(N, C) :- square_aux(N, N, C).