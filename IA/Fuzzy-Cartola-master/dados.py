# encoding: UTF-8
import pickle

class Jogador:
    def __init__(self, atleta):
        self.atleta = atleta
    def getJogador(self):
        return self.atleta 
    def getApelido(self):
        return self.atleta["apelido"]
    def getMediaPontos(self):
        return self.atleta["media"]
    def getPontos(self):
        return self.atleta["pontos"]
    def getJogos(self):
        return self.atleta["jogos"]
    def getPreco(self):
        return self.atleta["preco"]
    def getVarPreco(self):
        return self.atleta["variacao"]
    def getPosicao(self):
        return self.atleta["posicao"]["nome"]
    def getStatus(self):
        return self.atleta["status_id"]
    def getScout(self, nome):
        for i in self.atleta["scout"]:
            if(i['nome'] == nome):
                return i['quantidade']
        return 0;
    def getFaltasSofridas(self):
        return self.getScout('FS')
    def getPassesErrados(self):
        return self.getScout('PE')
    def getAssistencias(self):
        return self.getScout('A')

    def getFinalizacoesNaTrave(self):
        return self.getScout('FT')
    def getFinalizacoesDefendidas(self):
        return self.getScout('FD')
    def getFinalizacoesParaFora(self):
        return self.getScout('FF')
    def getFinalizacoes(self):
        return self.getFinalizacoesNaTrave()*2 + self.getFinalizacoesDefendidas()*2 + self.getFinalizacoesParaFora();

    def getGols(self):
        return self.getScout('G')
    def getImpedimentos(self):
        return self.getScout('I')
    def getPenaltisPerdidos(self):
        return self.getScout('PP')
    def getRouboDeBola(self):
        return self.getScout('RB')
    def getFaltasCometidas(self):
        return self.getScout('FC')
    def getGolsContra(self):
        return self.getScout('GC')
    def getCartoesAmarelo(self):
        return self.getScout('CA')
    def getCartoesVermelho(self):
        return self.getScout('CV')

    def getJogosSemTomarGol(self):
        return self.getScout('SG')

    # Só para goleiros
    def getDefesasDificies(self):
        return self.getScout('DD')
    def getDefesasPenaltis(self):
        return self.getScout('DP')
    def getGolsSofridos(self):
        return self.getScout('GS')

class Jogadores:
    def __init__(self, file_name):
        f = open(file_name, "rb")
        self.dados = pickle.load(f)
    def getListaJogadores(self):
        atletas = []
        for page in self.dados:
            atletas = atletas + page['atleta']
        jogadores = []
        for atleta in atletas:
            jogadores.append(Jogador(atleta));
        return jogadores

#jogadores = Jogadores("/home/vanderson/dev/repos/Fuzzy-Cartola/dadosCartola")
#a = jogadores.getListaJogadores()
#for i in a:
#    print(i.getApelido())
