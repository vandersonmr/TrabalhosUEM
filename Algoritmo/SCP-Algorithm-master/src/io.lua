function split(str, pat)
   local t = {}  -- NOTE: use {n = 0} in Lua-5.0
   local fpat = "(.-)" .. pat
    local last_end = 1
    local s, e, cap = str:find(fpat, 1)
    while s do
        if s ~= 1 or cap ~= "" then
            table.insert(t,cap)
        end
        last_end = e+1
        s, e, cap = str:find(fpat, last_end)
    end
    if last_end <= #str then
        cap = str:sub(last_end)
        table.insert(t, cap)
    end
    return t
end

function leColunasEmArquivo(nomeArquivo)
    next = next
    estrutura = {}
    i=0
    j=0
    for line in io.lines(nomeArquivo) do
        if (i==0) then
            estrutura.totalDeLinhas=line
            i=1
        else
            j=j+1
            aux = split(line," ")
            indice = tonumber(aux[1])

            estrutura[indice] = {}
            estrutura[indice].peso = aux[2]
            estrutura[indice].indice = indice

            for i=3,#aux do
                if estrutura[indice].valores == nil then
                    estrutura[indice].valores = {tonumber(aux[i])}
                else
                    table.insert(estrutura[indice].valores,tonumber(aux[i]))
                end
            end
        end
    end
    estrutura.totalDeColunas=j
    return estrutura
end

