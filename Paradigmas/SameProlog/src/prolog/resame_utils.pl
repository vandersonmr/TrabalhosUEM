% vim: set ft=prolog:
%
% Este arquivo contém predicados e funções auxiliares que você pode achar útil.
%
% Não é necessário alterar este arquivo.

:- use_module(library(readutil)).

%% read_matrix_file(+File, -M) is semidet
%
%  Lê para M uma matriz de números do arquivo File.

read_matrix_file(File, M) :-
    read_file_to_codes(File, In0, []),
    append(In1, [10], In0), % remove o último \n
    atom_codes(InputAtom, In1),
    atomic_list_concat(Lines, '\n', InputAtom),
    maplist(atom_numbers, Lines, T),
    reverse(T, P),
    transpose(P,M), !.

atom_numbers(Atom, Numbers) :-
    atomic_list_concat(Atoms, ' ', Atom),
    maplist(atom_number, Atoms, Numbers).

%% write_matrix(M) is det
%
%  Escreve na saída padrão a matriz M. Cada linha é escrita com a função
%  write_list/1.

write_matrix(M) :-
    transpose(M,P),
    reverse(P,T),
    maplist(write_list, T).

%% write_list(+A) is det
%
%  Escreve na saída padrão todos os elementos da lista A separados por espaço.

write_list([X]) :-
    write(X), put_char('\n'), !.
write_list([X|Xs]) :-
    write(X), put_char(' '),
    write_list(Xs).

%% transpose(?M, ?T) is semidet
%
%  Verdadeiro se T é a matriz transposta de M.

%transpose(M, []) :-
%    maplist(empty, M), !.
%transpose(M, [Hs|TTs]) :-
%    maplist(head, M, Hs),
%    maplist(tail, M, Ts),
%    transpose(Ts, TTs), !.

head([H|_], H).
tail([_|T], T).
empty([]).

nth0(V, In, Element, Rest) :-
    var(V), !,
    generate_nth(0,    V, In, Element, Rest).
nth0(V, In, Element, Rest) :-
    must_be(nonneg, V),
    find_nth0(V, In, Element, Rest).  

generate_nth(I, I,  [Head|Rest], Head, Rest).
generate_nth(I, IN, [H|List], El, [H|Rest]) :-
    I1 is I+1,
generate_nth(I1, IN, List, El, Rest).

find_nth0(0, [Head|Rest],  Head, Rest) :- !.
find_nth0(N, [Head|Rest0], Elem, [Head|Rest]) :-
    M is N-1,
    find_nth0(M, Rest0, Elem, Rest).

replace([_|T], Rest, 0,   New, Res) :- 
    rev(Rest,NRest),
    append(NRest,[New|T],Res).

replace([H|T], Rest, Idx, New, Res) :- 
    Idx1 is Idx-1, 
    replace(T,[H|Rest],Idx1,New,Res).

replace(List, Idx, New, Res) :- (New == [] -> nth0(Idx,List, _, Res) 
                                            ; replace(List,[],Idx,New,Res)).
size(A,B) :- length(A,0,B).
length([], N, N). 
length([_|T], L, N) :- L1 is L + 1, length(T, L1, N).

transpose([H|R],[H1|R1]):- 
   trans2([H|R],[H|R],[],[H1|R1],0),!.
trans2([A|_],_,_,[],N):-
   length(A,N).
trans2(M,[],H1,[H1|R1],N):-
   N1 is N+1,
   trans2(M,M,[],R1,N1).
trans2(M,[H|R],L,[H1|R1],N):-nth0(N,H,X),
   append(L,[X],L1),
   trans2(M,R,L1,[H1|R1],N).

accRev([H|T],A,R):-  accRev(T,[H|A],R).
accRev([],A,A). 
rev(L,R):-  accRev(L,[],R). 
