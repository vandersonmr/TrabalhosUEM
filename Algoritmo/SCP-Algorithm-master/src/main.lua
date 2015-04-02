
math.randomseed(os.time())

dofile("io.lua")
dofile("geradorSolucao.lua")
dofile("algoritmoGenetico.lua")

nomeArquivo = arg[1]

conjuntoDeColunas = leColunasEmArquivo(nomeArquivo)

melhorSolucao = buscarMelhorSolucao(conjuntoDeColunas)

