% Problema 4
% candidat(N: integer, E: integer)
% N - limita superioara
% E - un numar intre 1 si N
% model de flux (i, o) - nedeterminist
candidat(N, N) :-
    N >= 1.
candidat(N, E) :-
    N > 1,
    N1 is N - 1,
    candidat(N1, E).

% apartine(E: element, L: lista)
% E - elementul cautat
% L - lista in care se cauta
% model de flux (i, i) - determinist
apartine(E, [E|_]).
apartine(E, [H|T]) :-
    E \= H,
    apartine(E, T).

% permaux(N: integer, M: integer, Lg: integer, Col: lista, R: lista)
% N - numerele de la 1 la N
% M - diferenta minima in modul intre doua numere consecutive
% Lg - lungimea colectoarei Col
% Col - colectoarea (solutia construita pana acum)
% R - o solutie
% model de flux (i, i, i, i, o) - nedeterminist
permaux(N, _, N, Col, Col).
permaux(N, M, Lg, [H|T], R) :-
    Lg < N,
    candidat(N, E),
    \+ apartine(E, [H|T]),
    abs(E - H) >= M,
    Lg1 is Lg + 1,
    permaux(N, M, Lg1, [E, H|T], R).

% perm(N: integer, M: integer, R: lista)
% N - numerele de la 1 la N
% M - diferenta minima in modul
% R - o solutie
% model de flux (i, i, o) - nedeterminist
perm(N, M, R) :-
    candidat(N, E),
    permaux(N, M, 1, [E], R).

% toatePerm(N: integer, M: integer, L: lista de liste)
% N - numerele de la 1 la N
% M - diferenta minima in modul
% L - lista tuturor solutiilor
% model de flux (i, i, o) - determinist

toatePerm(N, M, L) :-
    findall(R, perm(N, M, R), L).

% Exemple de testare:
% ?- perm(4, 2, R).          R = [2,4,1,3] ; R = [3,1,4,2]
% ?- toatePerm(4, 2, L).     L = [[2,4,1,3],[3,1,4,2]]
% ?- toatePerm(3, 2, L).     L = []
% ?- toatePerm(3, 1, L).     L = [[1,2,3],[2,1,3],[1,3,2],[3,1,2],[2,3,1],[3,2,1]]
% ?- toatePerm(1, 5, L).     L = [[1]]
% ?- toatePerm(5, 2, L).     14 solutii
