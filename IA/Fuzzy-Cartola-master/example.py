from __future__ import division
import fuzzy.storage.fcl.Reader
import dados

jogadores = dados.Jogadores("/home/vanderson/dev/repos/Fuzzy-Cartola/dadosCartola")
a = jogadores.getListaJogadores();

system = fuzzy.storage.fcl.Reader.Reader().load_from_file("fuzzylogic.fc")

for jogador in a:
    if(jogador.getJogos() != 0):
        my_input = { 
                "RB" : (jogador.getRouboDeBola()/jogador.getJogos())*20, 
                "FC" : (jogador.getFaltasCometidas()/jogador.getJogos())*20, 
                "A"  : (jogador.getAssistencias()/jogador.getJogos())*200, 
                "F"  : (jogador.getFinalizacoes()/jogador.getJogos())*26.66,
                "FS"  : (jogador.getFaltasSofridas()/jogador.getJogos())*21.816,
                "Gols"  : (jogador.getGols()/jogador.getJogos())*154.54,
                "SG"  : (jogador.getJogosSemTomarGol()/jogador.getJogos())*100,
                "DD"  : (jogador.getDefesasDificies()/jogador.getJogos())*33.33,
                "GS"  : (jogador.getGolsSofridos()/jogador.getJogos())*33.33 }
        my_output = { "Meia" : 0.0, "Atacante": 0.0, 'Lateral': 0.0, 'Zagueiro' : 0.0, 'Goleiro': 0.0}
        system.calculate(my_input, my_output)
        if(jogador.getPosicao().encode('utf8') == 'Goleiro'):
            print(str(my_output)+":"+jogador.getApelido().encode('utf8') + " - "+ jogador.getPosicao().encode('utf8'))
