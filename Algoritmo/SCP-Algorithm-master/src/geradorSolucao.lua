function deepcopy(t)
    local t2 = {};
    for k,v in pairs(t) do
        if type(v) == "table" then
            t2[k] = deepcopy(v);
        else
            t2[k] = v;
        end
    end
    return t2;
end

function formataIndice(indice)
    return indice % tonumber(conjuntoDeColunas.totalDeColunas) + 1
end

function linhaCoberta(numeroDaLinha,solucao)
    return (solucao.linhasCobertas[numeroDaLinha] ~= nil)
end

function retornaColunaComIndice(indiceColuna)
    return conjuntoDeColunas[indiceColuna]
end

function colunaMelhoraSolucao(indiceColuna,solucao)
    local coluna = retornaColunaComIndice(indiceColuna)

    for numeroColuna,numeroDaLinha in pairs(coluna.valores) do
        if (not linhaCoberta(numeroDaLinha,solucao)) then
            return true
        end
    end

    return false
end

function desmarcarComoUsado(indice,solucao)
    solucao.colunaEmUso[indice] = nil
end

function marcaComoUsado(indice,solucao)
    solucao.colunaEmUso[indice] = 1
end

function removeColuna(indiceColuna,solucao)
    local coluna = retornaColunaComIndice(indiceColuna)
    
    for indice,valor in pairs(solucao.colunas) do
        if (valor.indice == indiceColuna) then
            table.remove(solucao.colunas,indice)
        end
    end
    
    solucao.peso = solucao.peso - coluna.peso

    for i = 1,#coluna.valores do
        local valorLinha = solucao.linhasCobertas[coluna.valores[i]]
        if (valorLinha ~= nil) then 
            valorLinha = valorLinha - 1
            if (valorLinha <= 0) then 
                valorLinha = nil
            end
            solucao.linhasCobertas[coluna.valores[i]] = valorLinha
        end
    end

    desmarcarComoUsado(indiceColuna,solucao)
end

function adicionaColuna(indiceColuna,solucao)
    local coluna = retornaColunaComIndice(indiceColuna)
    local totalDeLinhas = conjuntoDeColunas.totalDeLinhas

    table.insert(solucao.colunas,coluna)

    solucao.peso = solucao.peso + coluna.peso

    for i = 1,#coluna.valores do
        solucao.linhasCobertas[coluna.valores[i]]=1
    end

    marcaComoUsado(indiceColuna,solucao)
end

function estaCompleta(solucao)
    for numeroDaLinha = 1,conjuntoDeColunas.totalDeLinhas do
        if (not linhaCoberta(numeroDaLinha,solucao)) then
            return false
        end
    end

    return true
end

function colunaEstaEmUso(indice,solucao)
    return (solucao.colunaEmUso[indice] ~= nil) 
end

function geraIndiceColunaAleatoriaNaoUsadoNa(solucao)
    while(true) do 
        local indiceColuna = formataIndice(math.floor(math.random()*
        conjuntoDeColunas.totalDeColunas))

        if (not colunaEstaEmUso(indiceColuna, solucao)) then
            return indiceColuna
        end
    end
end

function geraSolucaoVazia()
    local solucao = {}
    solucao.linhasCobertas = {}
    solucao.peso = 0
    solucao.colunas = {}
    solucao.colunaEmUso = {}
    return solucao
end

function completaSolucao(solucao)
    local solucao = solucao

    while (not estaCompleta(solucao)) do
        local indiceColuna = geraIndiceColunaAleatoriaNaoUsadoNa(solucao)

        if (colunaMelhoraSolucao(indiceColuna,solucao)) then
            adicionaColuna(indiceColuna,solucao)
        end
    end

    return solucao
end

function geraNovaSolucao()
    local solucao = geraSolucaoVazia()

    solucao = completaSolucao(solucao)

    return solucao
end
