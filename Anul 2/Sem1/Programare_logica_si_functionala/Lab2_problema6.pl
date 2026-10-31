% Prob 6 punctul A
% adaugaLista(L: lista, C: lista, R: lista)
% L - lista ale carei elemente se pun in fata colectorului
% C - colectorul
% R - rezultatul: elementele lui L urmate de C
% model de flux (i, i, o), (i, i, i)

adaugaLista([],C,C).
adaugaLista([H|T],C,[H|R]) :-
    adaugaLista(T,C,R).


% inloc(L: lista, E: element, L1: lista, R: lista)
% L - lista data
% E - elementul care se inlocuieste
% L1 - lista cu care se inlocuieste E
% R - rezultatul
% model de flux (i, i, i, o), (i, i, i, i)

inloc([],_,_,[]).
inloc([H|T],E,L1,R) :-
    H = E,
    inloc(T,E,L1,R1),
    adaugaLista(L1,R1,R).
inloc([H|T],E,L1,[H|R]) :-
    H\=E,
    inloc(T,E,L1,R).


% Exemple de testare:
% ?- inloc([1,2,1,3,1,4], 1, [10,11], X).   X = [10,11,2,10,11,3,10,11,4]
% ?- inloc([1,2,3], 5, [10,11], X).         X = [1,2,3]
% ?- inloc([1,1], 1, [], X).                X = []
% ?- inloc([], 1, [10,11], X).              X = []
% ?- adaugaLista([1,2], [3,4], X).          X = [1,2,3,4]

% Punctul b
% inlocPrim(L: lista, L1: lista, R: lista)
% L - sublista
% L1 - lista cu care se inlocuieste primul element
% R - sublista in care toate aparitiile primului element sunt inlocuite cu L1
% model de flux (i, i, o), (i, i, i)
inlocPrim([],_,[]).
inlocPrim([H|T],L1,R):-
    inloc([H|T],H,L1,R).

% prelucrare(L: lista eterogena, L1: lista, R: lista eterogena)
% L - lista eterogena (numere intregi si liste de numere intregi)
% L1 - lista data
% R - rezultatul
% model de flux (i, i, o), (i, i, i)
prelucrare([],_,[]).
prelucrare([H|T],L1,[H1|R]):-
    is_list(H),
    inlocPrim(H,L1,H1),
    prelucrare(T,L1,R).
prelucrare([H|T],L1,[H|R]):-
    number(H),
    prelucrare(T,L1,R).


% Exemple de testare:
% ?- prelucrare([1,[4,1,4],3,6,[7,10,1,3,9],5,[1,1,1],7], [11,11], X).
%    X = [1,[11,11,1,11,11],3,6,[11,11,10,1,3,9],5,[11,11,11,11,11,11],7]
% ?- prelucrare([1,2,3], [11,11], X).       X = [1,2,3]
% ?- prelucrare([[5]], [0], X).             X = [[0]]
% ?- prelucrare([1,[],2], [11], X).         X = [1,[],2]
% ?- prelucrare([], [11], X).               X = []
