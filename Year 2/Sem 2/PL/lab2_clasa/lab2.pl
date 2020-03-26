% Exercitiul 5
scalarMult(_,[],[]).
scalarMult(X,[H|T], R) :- Hr is X * H, scalarMult(X,T,Tr), R = [Hr|Tr].
% scalarMult(X,[H|T], [Hr|Tr]) :- Hr is X * H, scalarMult(X,T,Tr).
%scalarMult(3,[2,7,4],Result).
%
%
%dot([2,5,6],[3,4,1],Result).

dot([],[], 0).
dot([H1|T1],[H2|T2],R):- Hr is H1* H2, dot(T1,T2,Tr), R is Tr+Hr.
% R se calculeaza dupa apelul recursiv deoarece are nevoie de Tr calculat

% max([4,2,6,8,1],Result).
max([],0).
% sau ne oprim pe ultimul element
% max([X],X).
max([H|T],Max) :- max(T,Max1), H >= Max1, Max = H.
max([H|T],Max) :- max(T,Max1), H < Max1, Max = Max1.

%sau 
%max([H|T],H) :- max(T,Max1), H >= Max1.
%max([H|T],Max1) :- max(T,Max1), H < Max1.
%sau 
%max([H|T],Max) :- (max(T,Max1), H >= Max1, Max = H); 
%                  (max(T,Max1), H < Max1, Max = Max1).

%Exercitiul 6 
% palindrome([r,e,d,i,v,i,d,e,r]).

inversare([],X,X).
inversare([H|T],L1,L2) :- inversare(T,[H|L1],L2).

palindrome(L):- inversare(L,[],L).

%Exercitiul 7
%remove_duplicates([a, b, a, c, d, d], List).

remove_duplicates([],[]).
remove_duplicates([H|T],L):- member(H,T), remove_duplicates(T,L);
     (   not(member(H,T)),remove_duplicates(T,L1), L = [H|L1]).








