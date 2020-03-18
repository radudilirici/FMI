fib(0, 1).
fib(1, 1).
fib(N, X) :- N1 is N - 1, fib(N1, X1),
			 N2 is N - 2, fib(N2, X2),
			 X is X1 + X2.

fib2(1, 1, 1).
fib2(N, Fn, Fn1) :- N1 is N - 1,
				   fib2(N1, Fn1, Fn2),
				   Fn is Fn1 + Fn2.

fib3(N, Fn) :- fib2(N, Fn, _).