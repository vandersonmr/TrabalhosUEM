SimpleSimulator
===============
    SimpleSimulator Copyright (C) 2013  
    Vanderson Martins do Rosario <vandersonmr2@gmail.com>,
    Victor Glauber Lopes Silva <victor_glauber@hotmail.com>,
    Diogo Takayuki Murata <diogomurat@gmail.com>.

    This program comes with ABSOLUTELY NO WARRANTY; for details type `--help'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `--copyright' for details.

    Para compilação:
        make
    Para exeucação:
        ruby /src/linker/linker.rb nomeArquivo.src
        ./sim -s nomeArquivo.obj
        parametros úteis:
            -S  (steps) Executa passo a passo;
            -m  (show Memory) Mostra memória. Pode ser usado com -S;
            -r  (Show registers) Mostra registradores. Pode ser usado com -S;
