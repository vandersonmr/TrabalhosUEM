# encoding: utf-8

import unittest
from unittest import TestCase
from eccheck import *

class GraphTest(TestCase):
    def setUp(self):
        self.g = Graph([1, 2, 3], [(1, 2), (3, 2)])
    
    def test_is_adj(self):
        g = self.g
        self.assertFalse(g.is_adj(1, 1))
        self.assertTrue (g.is_adj(1, 2))
        self.assertFalse(g.is_adj(1, 3))
        self.assertTrue (g.is_adj(2, 1))
        self.assertFalse(g.is_adj(2, 2))
        self.assertTrue (g.is_adj(2, 3))
        self.assertFalse(g.is_adj(3, 1))
        self.assertTrue (g.is_adj(3, 2))
        self.assertFalse(g.is_adj(3, 3))

class ParseTgfTest(TestCase):
    def setUp(self):
        self.tgf = ['1',
                    '2',
                    '3',
                    '#',
                    '1 2',
                    '3 2']

    def test_parse_pgf(self):
        g = parse_tgf(self.tgf)
        self.assertEqual(['1', '2', '3'], g.V)
        self.assertEqual(set([('1', '2'), ('3', '2')]), g.E)

class FakeTestResult(object):
    def __init__(self):
        self.errors = []

    def add_error(self, msg, expected=None, actual=None):
        self.errors.append((msg, expected, actual))

    def success(self):
        return not self.errors

class EulerianCycleTest(TestCase):
    def setUp(self):
        self.g = Graph([1, 2, 3, 4, 5],
                       [(1, 2), (1, 3),
                        (2, 3), (2, 4), (2, 5),
                        (3, 4), (3, 5)])

    def test_ec_check_success(self):
        test_result = FakeTestResult()
        eulerian_cycle_check(test_result, self.g, [1, 3, 4, 2, 5, 3, 2, 1])
        self.assertTrue(test_result.success())
        eulerian_cycle_check(test_result, self.g, [1, 2, 5, 3, 2, 4, 3, 1])
        self.assertTrue(test_result.success())

    def test_ec_check_not_cycle(self):
        test_result = FakeTestResult()
        eulerian_cycle_check(test_result, self.g, [1, 3, 4, 2, 5, 3, 2, 4])
        self.assertFalse(test_result.success())

    def test_ec_check_invalid_edge(self):
        test_result = FakeTestResult()
        eulerian_cycle_check(test_result, self.g, [1, 3, 4, 5, 1, 4, 2, 3, 5, 2, 1])
        self.assertFalse(test_result.success())
    
    def test_ec_check_duplicated_edge(self):
        test_result = FakeTestResult()
        eulerian_cycle_check(test_result, self.g, [1, 3, 4, 2, 5, 3, 2, 1, 3, 2, 1])
        self.assertFalse(test_result.success())

if __name__ == '__main__':
    unittest.main()
