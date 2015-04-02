dofile("../src/io.lua")
dofile("../src/geradorSolucao.lua")

describe("Testes do Gerador de Solucao", function()

    conjuntoDeColunas = leColunasEmArquivo("../data/Teste00.dat")

    it("Testa formata indice", function()
        assert.are.equals(1 , formataIndice(0 ))
        assert.are.equals(12, formataIndice(11))
        assert.are.equals(6 , formataIndice(5 ))
    end)
    
    it("Testa Linha coberta", function()
        solucao = geraSolucaoVazia()
        
        assert.are.equals(false, linhaCoberta(1,solucao))
        
        adicionaColuna(3,solucao)

        assert.are.equals(true , linhaCoberta(1,solucao))        
        assert.are.equals(false, linhaCoberta(4,solucao))
    end)
    
    it("Testa coluna Melhora solucao", function()
        solucao = geraSolucaoVazia()

        assert.are.equals(true , colunaMelhoraSolucao(1,solucao))

        adicionaColuna(1,solucao)

        assert.are.equals(false, colunaMelhoraSolucao(1,solucao))
        assert.are.equals(true , colunaMelhoraSolucao(2,solucao))
    end)
    
    it("Testa emUso", function()
        solucao = geraSolucaoVazia()
        assert.are.equals(false, colunaEstaEmUso(1,solucao))

        marcaComoUsado(1,solucao)
        assert.are.equals(true , colunaEstaEmUso(1,solucao))

        adicionaColuna(2,solucao)
        assert.are.equals(true, colunaEstaEmUso(2,solucao))
    end)
end)
