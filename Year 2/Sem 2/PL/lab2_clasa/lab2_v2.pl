% Lab 2
% Ex 5

scalarMult(_, [], []).
scalarMult(X, [H|T], [Hr|Tr]) :- Hr is X * H, scalarMult(X, T, Tr).
% scalarMult(3,[2,7,4],Result).
% Result = [6, 21, 12]


dot([],[],0).
dot([H1|T1],[H2|T2], R) :- dot(T1,T2,Tr), R is H1*H2 + Tr.

% dot([2,5,6],[3,4,1],Result).
% Result = 32

max([],0).
% max([X],X).
max([H|T],Max) :- max(T,Max1), H >= Max1, Max = H.
max([H|T],Max) :- max(T,Max1), H < Max1, Max = Max1.

%sau 
% max([H|T],Max) :- max(T,Max1), 
%    ( H >= Max1, Max = H;  H < Max1, Max = Max1).

%sau
% max([H|T],H) :- max(T,Max1), H >= Max1.
% max([H|T],Max1) :- max(T,Max1), H < Max1.


% Ex 6

% rev([1,2,3,2,1],[],[1,2,3,2,1]).

rev([],L,L).
rev([H|T], L,Laux):- rev(T,[H|L],Laux).

palindrome(L) :- rev(L,[],L1), L = L1.
% same as
% palindrome(L) :- rev(L,[],L).

% remove_duplicates([a, b, a, c, d, d], List).

remove_duplicates([],[]).
remove_duplicates([H|T], Lr):- 
    ( member(H,T), remove_duplicates(T,Lr));
    ( not(member(H,T)), remove_duplicates(T,Lr1), Lr = [H|Lr1]).













