# encoding: utf-8

import math
import re

SPACES = re.compile(r"\s+")
INF = float('+infinity')

class Graph:
    def __init__(self, costs):
        self.costs = costs
        self.n = len(costs)

    def vertices(self):
        return range(self.n)

    def cost(self, u, v):
        return self.costs[u][v]

def parse_tsp(lines):
    points = []
    for line in lines:
        _, x, y = map(float, [s for s in SPACES.split(line.strip())])
        points.append((x, y))
    n = len(points)
    costs = [[INF] * n for i in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            costs[i][j] = costs[j][i] = distance(points[i], points[j])
    return Graph(costs)

def distance(p1, p2):
    dx = p1[0] - p2[0]
    dy = p1[1] - p2[1]
    return int(math.hypot(dx, dy) + 0.5)

def tsp_check(test_result, g, tour, cost):
    if tour[0] != tour[-1]:
        test_result.add_error(u'O primeiro vértice não é igual ao último')
        return

    for v in g.vertices():
        v += 1
        if v not in tour:
            test_result.add_error(u'Vértice não está no caminho: %d', v)

    visited = set()
    for v in tour[:-1]:
        if v in visited:
            test_result.add_error(u'Vértice repetido: %d', v)
        visited.add(v)

    if not test_result.success():
        return
    
    c = 0
    for i in xrange(len(tour) - 1):
        u = tour[i]
        v = tour[i + 1]
        c += g.cost(u - 1, v - 1)
    if c != cost:
        test_result.add_error(u'Custo', c, cost)

def tsp_check_main(test_result, case, expected, program_result):
    g = parse_tsp(readlines(case))
    try:
        actual = map(int, program_result.out.splitlines())
        if len(actual) < 3:
            test_result.add_error(u'formatação: poucos vértices')
            return
        tsp_check(test_result, g, actual[1:], actual[0])
    except ValueError as e:
        test_result.add_error(u'formatação: valor não é inteiro')

# utilidades
def readlines(infile):
    with open(infile) as f:
        return f.read().splitlines()
