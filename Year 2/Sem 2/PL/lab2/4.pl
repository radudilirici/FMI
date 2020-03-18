all_a([]).
all_a([a | Tail]) :- all_a(Tail).

no_a([]).
no_a([X | T]) :- X \= a, no_a(T).

trans_a_b([], []).
trans_a_b([a | Ta], [b | Tb]) :- trans_a_b(Ta, Tb).