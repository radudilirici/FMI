% Lab 3

% Crossword puzzle

word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).


crosswd(V1, V2, V3, H1, H2, H3):- 
    word(V1,_, X1, _, X2, _, X3,_),
    word(V2,_, Y1, _, Y2, _, Y3,_),
    word(V3,_, Z1, _, Z2, _, Z3,_),
    word(H1,_, X1, _, Y1, _, Z1,_),
    word(H2,_, X2, _, Y2, _, Z2,_),
    word(H3,_, X3, _, Y3, _, Z3,_).

born(jan, date(20,3,1977)).
born(jeroen, date(2,2,1992)).
born(joris, date(17,3,1995)).
born(jelle, date(1,1,2004)).
born(joan, date(24,12,0)).
born(joop, date(30,4,1989)).
born(jannecke, date(17,3,1993)).
born(jaap, date(16,11,1995)).


year(A,P):- born(P,date(_,_,A)).

before(date(D1,M1,Y1), date(D2,M2,Y2)):- 
    Y1 < Y2;
    Y1 = Y2, M1 < M2;
    Y1 = Y2, M1 = M2, D1 < D2. 

older(P1,P2) :- born(P1, Data1), born(P2,Data2), before(Data1,Data2).

% Maze
/*
connected(1,2).
connected(3,4).
connected(5,6).
connected(7,8).
connected(9,10).
connected(12,13).
connected(13,14).
connected(15,16).
connected(17,18).
connected(19,20).
connected(4,1).
connected(6,3).
connected(4,7).
connected(6,11).
connected(14,9).
connected(11,15).
connected(16,12).
connected(14,17).
connected(16,19).
*/
connected(1,2).
connected(2,1).
connected(1,3).
connected(3,4).

path(P1,P2):- connected(P1,P2). 
path(P1,P2):- connected(P1,P3), path(P3,P2). 

path(P1,P2,L):- connected(P1,P2), write(L). 
path(P1,P2,L):- connected(P1,P3), not(member(P3, L)), path(P3,P2,[P3|L]).

path2(P1,P2) :- path(P1,P2,[P1]).

% Ex 4

successor(X,[x|X]).

plus(X1,X2,X3):- append(X1,X2,X3).

times([],_,[]).
times([x|X1], X2, X3):- times(X1,X2,X4), plus(X2,X4, X3).  

% Ex 5

element_at([X|_], 1, X).
element_at([_|T],N,X):- N > 1, N1 is N-1, element_at(T, N1, X). 


% Ex 6


/* Animal  database */

animal(alligator).
animal(tortue) .
animal(caribou).
animal(ours) .
animal(cheval) .
animal(vache) .
animal(lapin) .

mutant(M):- 
    animal(A1), animal(A2), A1 \= A2,
    name(A1,L1), name(A2,L2),
    append(P1, S1, L1), P1 \= [], S1 \= [],
    append(P2, S2, L2), P2 \= [], S2 \= [], S1 = P2, 
    append(L1, S2, Lm), name(M,Lm). 


mutant(M, L):- 
    member(A1,L), member(A2,L), A1 \= A2,
    name(A1,L1), name(A2,L2),
    append(P1, S1, L1), P1 \= [], S1 \= [],
    append(P2, S2, L2), P2 \= [], S2 \= [], S1 = P2, 
    append(L1, S2, Lm), name(M,Lm). 











