# encoding: utf-8

import unittest
from unittest import TestCase
from tspcheck import *

class ParseTspFileTest(TestCase):
    def test_parse_tsp_file(self):
        g = parse_tsp(['1 1 1',
                       '2 3 2',
                       '3 1 4',
                       '4 5 5'])
        self.assertEqual(g.costs, [[INF, 2, 3, 6],
                                   [2, INF, 3, 4],
                                   [3, 3, INF, 4],
                                   [6, 4, 4, INF]])

class FakeTestResult(object):
    def __init__(self):
        self.errors = []

    def add_error(self, msg, expected=None, actual=None):
        self.errors.append((msg, expected, actual))

    def success(self):
        return not self.errors

class TspCheckTest(TestCase):
    def setUp(self):
        self.g = Graph([[INF, 2, 3, 6],
                        [2, INF, 3, 4],
                        [3, 3, INF, 4],
                        [6, 4, 4, INF]])

    def test_tsp_check_success(self):
        test_result = FakeTestResult()
        tsp_check(test_result, self.g, [1, 2, 3, 4, 1], 15)
        self.assertTrue(test_result.success())
        tsp_check(test_result, self.g, [1, 2, 4, 3, 1], 13)
        self.assertTrue(test_result.success())

    def test_tsp_check_not_cycle(self):
        test_result = FakeTestResult()
        tsp_check(test_result, self.g, [1, 2, 3, 4], 9)
        self.assertFalse(test_result.success())

    def test_tsp_check_missing_vertex(self):
        test_result = FakeTestResult()
        tsp_check(test_result, self.g, [1, 2, 3, 1], 8)
        self.assertFalse(test_result.success())

    def test_tsp_check_duplicated_vertex(self):
        test_result = FakeTestResult()
        tsp_check(test_result, self.g, [1, 2, 3, 2, 4, 1], 18)
        self.assertFalse(test_result.success())

    def test_tsp_check_cost(self):
        test_result = FakeTestResult()
        tsp_check(test_result, self.g, [1, 2, 3, 4, 1], 18)
        self.assertFalse(test_result.success())

if __name__ == '__main__':
    unittest.main()
