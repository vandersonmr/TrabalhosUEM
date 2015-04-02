# encoding: utf-8

# Representacao de conjuntos, em geral não é eficiente mas é simples
class Graph:
    def __init__(self, V, E):
        self.V = V
        self.E = set(E)

    def is_adj(self, u, v):
        return (u, v) in self.E or (v, u) in self.E

def parse_tgf(lines):
    sharp = lines.index('#')
    V = lines[:sharp]
    E = [tuple(line.split()) for line in lines[sharp + 1:]]
    return Graph(V, E)

def eulerian_cycle_check(test_result, g, cycle):
    if cycle[0] != cycle[-1]:
        test_result.add_error(u'O primeiro vértice não é igual ao último')
        return
    
    visited = set()
    for i in xrange(len(cycle) - 1):
        u = cycle[i]
        v = cycle[i + 1]
        if not g.is_adj(u, v):         
            test_result.add_error(u'Aresta não faz parte do grafo: (%s, %s)' % (u, v))
        if (u, v) in visited:
            test_result.add_error(u'Aresta repetida: (%s, %s) ou (%s, %s)' % (u, v, v, u))
        visited.add((u, v))
        visited.add((v, u))

    if not test_result.success():
        return

    for u, v in g.E:
        if (u, v) not in visited:
            test_result.add_error(u'Aresta não visitada: (%s, %s)' % (u, v))

def eulerian_cycle_check_main(test_result, case, expected, program_result):
    g = parse_tgf(readlines(case))
    actual = program_result.out.splitlines()
    if len(actual) < 2:
        test_result.add_error(u'formatação: poucos valores')
        return
    eulerian_cycle_check(test_result, g, actual)

# utilidades
def readlines(infile):
    with open(infile) as f:
        return f.read().splitlines()
