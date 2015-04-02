% vim: set ft=prolog:

% Usa o arquivo plunit.pl se é uma versão é < 6.0
:- current_prolog_flag(version, V), V < 60000, use_module(plunit) ; true.
% Usa o arquivo plunit.pl que vem com o Prolog se a versão é > 6.0.0
:- current_prolog_flag(version, V), V > 60000, use_module(library(plunit)) ; true.

:- consult(resame).

:- begin_tests(resame).

% Os testes são escritos usando a biblioteca plunit. Veja a documentação em
% http://www.swi-prolog.org/pldoc/package/plunit.html
%
% Para executar os testes, utilize o comando make plunit (no diretório resame)

% Considerando o seguinde jogo
% 2 | 2 1 3 1
% 1 | 2 2 2 3
% 0 | 2 3 3 1
% --+---------
%   | 0 1 2 3
% Os possíveis grupos com mais de um elemento são
% cor 2 - (0,0), (1,0), (1,1), (1,2), (2,0) e
% cor 3 - (0,1), (0,2)
%
% Como a ordem dos elementos em um grupo não é importante, o grupo é ordenado
% no teste.

test(group_1_2, G == [pos(0,0), pos(1,0), pos(1,1), pos(1,2), pos(2,0)]) :-
    group([[2, 2, 2], [3, 2, 1], [3, 2, 3], [1, 3, 1]], pos(1, 2), H),
    sort(H, G).

test(group_0_2, G == [pos(0,1), pos(0,2)]) :-
    group([[2, 2, 2], [3, 2, 1], [3, 2, 3], [1, 3, 1]], pos(0, 2), H),
    sort(H, G).

% O predicado grupo/2 é não determinístico e deve gerar todos os grupos.  A
% ordem que os grupos são gerados, não é importante, por isto é usado set no
% teste.
test(group, G == [[pos(0,0), pos(1,0), pos(1,1), pos(1,2), pos(2,0)],
                      [pos(0,1), pos(0,2)]]) :-
    group([[2, 2, 2], [3, 2, 1], [3, 2, 3], [1, 3, 1]], H),
    sort(H, G)
    , write(H), nl % se o teste estiver falhando, você pode
    .               % remover este comentario para imprimir a resposta e ver o
                    % que esta errado.

% Considerando o seguinde jogo
% 2 | 2 1 3 1
% 1 | 2 2 2 3
% 0 | 2 3 3 1
% --+---------
%   | 0 1 2 3
% Remover o grupo em (1, 2) - [(0,0), (1,0), (1,1), (1,2), (2,0)], gera o jogo
% 2 | 0 0 1 0
% 1 | 1 3 3 0
% 0 | 3 3 1 0
% --+---------
%   | 0 1 2 3
test(remove_group, NewSame == [[3, 1], [3, 3], [1, 3, 1]]) :-
    remove_group([[2, 2, 2], [3, 2, 1], [3, 2, 3], [1, 3, 1]],
                 [pos(0,0), pos(1,0), pos(1,1), pos(1,2), pos(2,0)],
                 NewSame).

:- end_tests(resame).
