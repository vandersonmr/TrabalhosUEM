dofile("../src/io.lua")

describe("Testes IO", function()
    it("Checa leitura da quantidade de linhas", function()
        assert.are.equals('6' , leColunasEmArquivo("../data/Teste00.dat")
                                                          .totalDeLinhas)
        assert.are.equals('50', leColunasEmArquivo("../data/Teste01.dat")
                                                          .totalDeLinhas)
        assert.are.equals('50', leColunasEmArquivo("../data/Teste02.dat")
                                                          .totalDeLinhas)
    end)
    
    it("Checa leitura da quantidade de colunas", function()
        assert.are.equals(12 , leColunasEmArquivo("../data/Teste00.dat")
                                                        .totalDeColunas)
        assert.are.equals(300, leColunasEmArquivo("../data/Teste01.dat")
                                                        .totalDeColunas)
        assert.are.equals(500, leColunasEmArquivo("../data/Teste02.dat")
                                                        .totalDeColunas)
    end)
    
    it("Checa leitura de peso", function()
        indiceColuna = 10

        assert.are.equals('3.00' , leColunasEmArquivo("../data/Teste00.dat")
                                                        [indiceColuna].peso)
        assert.are.equals('58.55', leColunasEmArquivo("../data/Teste01.dat")
                                                        [indiceColuna].peso)
        assert.are.equals('66.68', leColunasEmArquivo("../data/Teste02.dat")
                                                        [indiceColuna].peso)
    end)

    it("Checa leitura de linhas nas colunas", function()
        indiceColuna = 5

        assert.are.equals(6 , leColunasEmArquivo("../data/Teste00.dat")
                                             [indiceColuna].valores[2])
        assert.are.equals(39, leColunasEmArquivo("../data/Teste01.dat")
                                             [indiceColuna].valores[2])
        assert.are.equals(19, leColunasEmArquivo("../data/Teste02.dat")
                                             [indiceColuna].valores[2])
    end)
end)
