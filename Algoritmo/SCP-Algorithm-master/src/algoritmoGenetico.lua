criterioDeParada = 300
pesoDeMelhorar = -0
probabilidadeDeCopiarGene = 40
tamanhoDaPopulacaoInicial = 50
chanceDeMutar = 15
quantidadeDeGenesMutados = 1
quantidadeDeFilhos = 50
r = 5
quantidadeDeVizinhosNaBuscaLocal = 500

function geraPopulacao(n)
    local conjuntoDeSolucoes = {}

    for i = 0,n do
        conjuntoDeSolucoes[i] = geraNovaSolucao()
    end

    return conjuntoDeSolucoes
end

function insereColunasAleatorias(pai,filho)
    for chave,coluna in pairs(pai.colunas) do
        if (not colunaEstaEmUso(coluna.indice,filho)) then
            if (math.random(0,100)
                + (colunaMelhoraSolucao(coluna.indice,filho) and pesoDeMelhorar or 0)
          < probabilidadeDeCopiarGene) then

                adicionaColuna(coluna.indice,filho)
            end
        end
    end
end

-- n sexo aleatório entre os individuos.
function geraFilho(pais)
    local filho = geraSolucaoVazia()
    insereColunasAleatorias(pais[1],filho)
    insereColunasAleatorias(pais[2],filho)
    return filho
end

function mutar(solucao)
    local mutacoes = 0
    for indice,coluna in pairs(solucao.colunas) do
        if (mutacoes > quantidadeDeGenesMutados) then
            return solucao
        end
        if (math.random(0,100) < 50) then
            mutacoes = mutacoes + 1
            removeColuna(coluna.indice,solucao)
            indiceAleatorio = geraIndiceColunaAleatoriaNaoUsadoNa(solucao)
            adicionaColuna(indiceAleatorio,solucao)
        end
    end
    return solucao
end

function getMelhor(populacao)
    local melhor = populacao[1]
    local melhorPeso = populacao[1].peso
    for indice,solucao in pairs(populacao) do
        if (solucao.peso < melhorPeso) then
            melhor = solucao
            melhorPeso = solucao.peso
        end
    end
    return melhor
end

function isValido(solucao)
    return estaCompleta(solucao)
end


ultimaMedia = 0
contador = 0
function continuaMelhorando(populacao)
    --local mediaPeso = calculaMediaPeso(populacao)
    --if (math.abs(mediaPeso - ultimaMedia) < 1) then
    --    contador = contador + 1
    --end
    --ultimaMedia = mediaPeso
    --return (contador < criterioDeParada)
    return (math.abs(calculaMediaPeso(populacao)
        - getMelhor(populacao).peso) >= 5)
        
end

function pesoTotalPopulacao(populacao)
    local pesoTotal=0

    for indice,solucao in pairs(populacao) do
        pesoTotal=pesoTotal+solucao.peso
    end

    return pesoTotal
end

function retornaSolucaoMaisPesada(populacao)
    local maisPesada = 0
    local peso = 0
    for indice,solucao in pairs(populacao) do
        if (solucao.peso > peso) then
            peso = solucao.peso
            maisPesada = solucao
        end
    end
    return maisPesada
end

function retornaPaisRandomicosDe(populacao)
    local pesoTotal = pesoTotalPopulacao(populacao)
    local maiorPeso = retornaSolucaoMaisPesada(populacao).peso + 1
    local pais = {}

    while(true) do
        for indice,solucao in pairs(populacao) do
            if (#pais == 2) then return pais end
            local probabilidade = (maiorPeso - solucao.peso)    
            local valorAleatorio = math.random(0,maiorPeso)

            if (valorAleatorio <= probabilidade) then
                table.insert(pais,solucao)
            end
        end
    end
end

function calculaMediaPeso(populacao)
    local pesoTotal = pesoTotalPopulacao(populacao)
    return pesoTotal/#populacao
end

function selecionaNovaPopulacao(populacao,novaPopulacao)
    local mediaPeso = calculaMediaPeso(populacao)
    local adicionados = 0
    
    for indice,solucao in pairs(novaPopulacao) do
        if (solucao.peso < mediaPeso) then
            table.insert(populacao,solucao)
            adicionados = adicionados + 1
        end
    end

    for indice,solucao in pairs(populacao) do
        if (solucao.peso > mediaPeso and adicionados > 0) then
            adicionados = adicionados - 1
            table.remove(populacao,indice)
        end
    end

    return populacao
end

function imprimeValoresDeUmaColuna(coluna)
    for t = 1,#coluna.valores do
        print(coluna.valores[t])
    end
end

function imprimeColunas(colunas)
    for j = 1,#colunas do
        imprimeValoresDeUmaColuna(colunas[j])
        print("")
    end
end

function imprimeIndicesColunas(colunas)
    for j = 1,#colunas do
        print(colunas[j].indice)
    end
end

function imprimePopulacao(populacao)
    for i = 0,#populacao do 
        imprimeColunas(populacao[i].colunas)
        print("Peso: "..populacao[i].peso)
        print("---------------------")
    end
end

function encontrarMelhorVizinho(solucao)
    local melhorVizinho = deepcopy(solucao)
    local solucao = deepcopy(solucao)
    for i = 1,quantidadeDeVizinhosNaBuscaLocal do  
        local indiceColuna = math.random(1,#solucao.colunas)
        removeColuna(solucao.colunas[indiceColuna].indice,solucao)
        local indiceNovaColuna = geraIndiceColunaAleatoriaNaoUsadoNa(solucao)
        adicionaColuna(indiceNovaColuna,solucao)
        if (isValido(solucao)) then
            if (solucao.peso < melhorVizinho.peso) then
                return deepcopy(solucao)
            else
                solucao = deepcopy(melhorVizinho)
            end
        end
    end

    return melhorVizinho 
end

function VND(solucao)
    local S0 = solucao
    local S1 = {}
    local k = 1
    while (k <= r) do
        S1 = encontrarMelhorVizinho(S0)
        if (S1.peso < S0.peso) then
            S0 = deepcopy(S1)
            k = 1
        else
            k = k + 1
        end
    end
    return S1
end

function buscaMinimoLocal(populacao)
    for i = 1,#populacao do
        populacao[i]=VND(populacao[i])
    end
    return populacao
end

function buscarMelhorSolucao(conjuntoDeColunas)
    conjuntoDeColunas = conjuntoDeColunas 
    local populacao = geraPopulacao(tamanhoDaPopulacaoInicial)

    print("media1: "..calculaMediaPeso(populacao))
    populacao = buscaMinimoLocal(populacao)
    print("media2: "..calculaMediaPeso(populacao))

    local pais = {}
    local filho = {}
    local filhoMutado = {}

    while (continuaMelhorando(populacao)) do

        local populacaoNova = {}
        while(#populacaoNova ~= quantidadeDeFilhos) do

            pais = retornaPaisRandomicosDe(populacao)
            filho = geraFilho(pais)

            if (math.random(0,100) < chanceDeMutar) then
                filho = mutar(filho)
            end

            if (isValido(filho)) then 
                table.insert(populacaoNova,filho)
            end

        end
        
        print(calculaMediaPeso(populacao).." - "..getMelhor(populacao).peso)
        
        populacaoNova = buscaMinimoLocal(populacaoNova)
        populacao = selecionaNovaPopulacao(populacao,populacaoNova)
        -- Busca local sobre todos os individuos 
        -- da populacao intermediaria

    end
    
    melhor = VND(getMelhor(populacao))
    print("----------------")
    imprimeIndicesColunas(melhor.colunas)
    print(melhor.peso)
end

