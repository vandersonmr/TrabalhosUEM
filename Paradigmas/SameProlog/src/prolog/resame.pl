% vim: set ft=prolog:

% Neste arquivo estão especificados os predicados que devem ser implementados.
% Você pode criar predicados auxiliares quando necessário.
%
% No arquivo resame_testes.pl estão os testes para alguns predicados.
%
% Para implementar cada predicado, primeiro você deve ler e entender a
% especificação e o teste.
%
% A especificação dos parâmetros dos predicados segue o formato descrito em
% http://www.swi-prolog.org/pldoc/doc_for?object=section%282,%274.1%27,swi%28%27/doc/Manual/preddesc.html%27%29%29
%
% Um Same same é representado por uma lista de Columns, sem os elementos nulos
% (zeros).
% Por exemplo, o jogo
% 2 | 3 0 0 0
% 1 | 2 2 2 0
% 0 | 2 3 3 1
% --+--------
%   | 0 1 2 3
% é representado como [[2, 2, 3], [3, 2], [3, 2], [1]].
% O tamanho deste jogo é 3x4 (lines x Columns).
%
% Uma posição no jogo é representado por uma estrutura pos com dois argumentos
% (lin, col), onde lin é o número da line e col é o número da Column.  No
% exemplo anterior, a posição pos(0, 1) tem cor 3, e a posição pos(1, 2) tem
% cor 2.

% Você pode utilizar os predicados definidos no arquivo resame_utils.pl
:- consult(resame_utils).

%% main(+File) is det
%
%  Carrega um jogo same do arquivo File e imprime uma resolução na saída padrão
%  ou sem-solucao se o jogo não tem solução.

main(File) :-
    read_matrix_file(File,M),
    solve(M,Moves),
    print_results(M,Moves).

% print_results(Same, Resultados)
% Imprimi uma lista de movimentos na saída padrão formatado da forma que foi
% especificado. (Link das especificações no topo).
print_results(Same, [pos(X,Y)|T]) :-
	write(X), put_char(' '), write(Y),
	put_char('\n'),
	group(Same, pos(X,Y), GroupNO),!, 
	sort(GroupNO,GroupN),
	reverse(GroupN,Group),
	zero_group(Same,Group,NewSame),
	put_char('\n'),
	write_matrix(NewSame),
	put_char('\n'),
	print_results(NewSame,T).

%% solve(+Same, -Moves) is nondet
%
%  Verdadeiro se Moves é uma sequência de jogadas (lista de posições) que
%  quando realizadas ("clicadas") resolvem o jogo Same.
%  Este predicado não tem teste de unidade. Ele é testado pelo testador.

solve([]  , []).
solve(Same, [M|Moves]) :-
    group(Same, Group),
    remove_group(Same, Group, NewSame),
    [M|_] = Group,
    solve(NewSame, Moves),!.

%% group(+Same, ?Group) is nondet
%
%  Verdadeiro se Group é um grupo de Same. Group é uma lista de posições
%  (estrutura pos(lin,col)). Este predicado é não determinístico e deve ser
%  capaz de gerar todos os grupos de Same. Este predicado não deve gerar grupos
%  repetidos. Este predicado e group/3 para vão utilizar os mesmos precicados
%  auxiliares.
group(Same, Group) :-
    pos_validate(Same, pos(X,Y)),
    group(Same, pos(X,Y), NewGroup),
    size(NewGroup, Size),
    Size > 1,
    Group = NewGroup.

% Caso o primeiro group falhe, o segundo continua procurando grupos de forma
% recursiva.
group(Same, Group) :-
    pos_validate(Same, pos(X,Y)),
    group(Same, pos(X,Y), _, NewSame),
    group(NewSame, Group).


% Troca a cor de um Same na posição X,Y e retorna o novo same em NewSame.
change_color(Same, pos(X,Y), Color, NewSame) :-
    nth0(Y,Same,Column),
    replace(Column, X, Color,NewColumn),
    replace(Same, Y,NewColumn,NewSame).

% Retorna verdadeiro se todos os elementos da lista forem 0. Ou brancos (DL).
white([]).
white([0|T]) :- white(T).

% Zera a posição X,Y. E segue a lógica da impressão que se a coluna inteira for
% branca (white(List)) então ela é retirada e é dado um shift.
zero_pos(Same, pos(X,Y), NewSame) :-
    nth0(Y,Same,Column),
    remove_line(Column,X,NColumn),
    append(NColumn,[0],NewColumn),
    (white(NewColumn) -> remove_line(Same,Y,NSame),
			   append(NSame,[NewColumn],NewSame)
    			;  replace(Same,Y,NewColumn,NewSame)).

% Zera todas as posições da lista [H|T].
zero_group(Same, []   , Same).
zero_group(Same, [H|T], NewSame) :-
    zero_pos(Same, H, NSame),
    zero_group(NSame, T, NewSame).   	

% Verdadeiro se pos(X,Y) é uma posição valida.
validate(Same, pos(X,Y)) :-
    color_pos(Same,pos(X,Y),Color),
    Color \= 0.

% Gera uma posição valida.
pos_validate(Same, pos(X,Y)) :-
    validate(Same,pos(X,Y)),!.

% Retorna em Color a cor na posição pos(X,Y)
color_pos(Same, pos(X,Y), Color) :- 
    nth0(Y,Same, Column), 
    nth0(X,Column, Color).

% Verdadeiro se a cor na posição pos(X,Y) tiver cor igual a Color.
same_color(Same, pos(X,Y), Color) :-
    color_pos(Same, pos(X,Y), Color).

% Verdadeiro se a pos(X,Y) é um vizinho valido (Mesma cor de Color
% e diferente de zero (branco)). 
neighbor_valido(Same, Color, pos(X,Y)) :-
    validate(Same,pos(X,Y)),
    same_color(Same,pos(X,Y),Color).

% Invalida  (pinta de branco) todas as posições da lista [H|T].
invalidates_pos(Same, []   , Same).
invalidates_pos(Same, [H|T], SameFinal) :- 
    change_color(Same,H,0,NewSame),
    invalidates_pos(NewSame,T,SameFinal).
    
% Retorna todos os vizinhos de até uma posição de distância de
% pos(X,Y) que são válidos.
neighbors_same_color(Same, pos(X,Y),Color, Neighbors,NewSame) :-
    X1 is X+1,
    X2 is X-1,
    Y1 is Y+1,
    Y2 is Y-1,
    include(neighbor_valido(Same,Color),
            [pos(X1,Y),pos(X2,Y),pos(X,Y1),pos(X,Y2)],Neighbors),
    invalidates_pos(Same,Neighbors,NewSame).

% BFS que busca todas as posições vizinhas e retorna o group de posições
% vizinhas e o Same sem essas posições.
visit_neighbors_same_color(Same, []   ,     _, Group     , Group, Same).
visit_neighbors_same_color(Same, [H|T], Color, GroupAtual, Group, SameFinal) :-
    change_color(Same, H, 0, NewSame1),
    neighbors_same_color(NewSame1, H, Color, Neighbors, NewSame),
    append(T, Neighbors, News),
    visit_neighbors_same_color(NewSame, News, Color, [H|GroupAtual], Group,SameFinal).

group(Same, pos(X,Y), Group) :-
    color_pos(Same, pos(X,Y), Color),
    visit_neighbors_same_color(Same,[pos(X,Y)],Color, [], Group,_).

group(Same, pos(X,Y), Group,NewSame) :-
    color_pos(Same, pos(X,Y), Color),
    visit_neighbors_same_color(Same,[pos(X,Y)],Color, [], Group, NewSame).

%% remove_group(+Same, +Group, -NewSame) is semidet
%
%  Verdadeiro se NewSame é obtido de Same removendo os elemento especificados
%  em Group. A remoção é feita de acordo com as regras do jogo same.
%  Dica:
%    - crie um predicado auxiliar remove_Column_group, que remove os elementos
%    de uma Column específica
remove_line(Column, X, NewColumn) :-
    nth0(X,Column, _,NewColumn).

% Remove uma posição pos(X,Y) de um Same.
remove_pos(Same, pos(X,Y), NewSame) :-
    nth0(Y,Same,Column),
    remove_line(Column,X,NewColumn),
    replace(Same,Y,NewColumn,NewSame).

% Remove um grupo posições QUE DEVEM ESTAR ordenados
% de um same.
remove_group_sorted(Same, []   , Same).
remove_group_sorted(Same, [H|T], NewSame) :-
    remove_pos(Same, H, NSame),
    remove_group_sorted(NSame, T, NewSame).

% Remove um grupo de posições NÃO NECESSÁRIAMENTE ORDENADO
% de um same
remove_group(Same, Group, NewSame) :-
    sort(Group, SortedGroup),
    rev(SortedGroup,NewGroup),
    remove_group_sorted(Same,NewGroup,NewSame).
