% vim: set ft=prolog:
%
% Este arquivo contém o predicado principal que é executado pelo testador.
%
% Os predicados deste arquivo dependem dos predicados do arquivo resame.pl.
% Você deve implementar todos os predicados especificados em resame.pl.
%
% Você não deve editar este arquivo.

:- consult(resame).

main :-
    current_prolog_flag(argv, Argv),
    append(_, [--, File|_], Argv), !,
    main(File).
