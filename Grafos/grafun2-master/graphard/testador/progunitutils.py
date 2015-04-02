#!/usr/bin/python
# encoding: utf-8

import sys
import os
import subprocess
from time import time
from progunit import *

DEFAULT_FILE_EXP_EXT = ".out"
DEFAULT_PROG_RUN="/run"
DEFAULT_PROG_BUILD="/build"
DEFAULT_LOG_FILE="testes.log"

def run_progs_cases(check_fun, progs, cases, reporter):
    progs = [p for p in progs if p.build()]
    test_cases = create_test_cases(check_fun, progs, cases)
    runner = Runner(test_cases, reporter)
    runner.run()

def create_test_cases(check_fun, progs, cases):
    tests = []
    for prog in progs:
        m = max(len(prog.desc() + ' ' + case.input) for case in cases)
        for case in cases:
            description = (prog.desc() + ' ' + case.input).ljust(m)
            program = prog.create_program([case.get_abs_input()])
            check = case.create_check(check_fun)
            tests.append(TestCase(description, program, check))
    return tests

class Case(object):
    def __init__(self, input, expected):
        self.input = input
        self.expected = expected

    def get_abs_input(self):
        return os.path.abspath(self.input)

    def get_abs_expected(self):
        return os.path.abspath(self.expected)

    def create_check(self, check_fun):
        def check(test_result, program_result):
            return check_fun(test_result,
                             self.get_abs_input(),
                             self.get_abs_expected(),
                             program_result)
        return check

class ProgramInfo(object):
    def __init__(self, cmd_build, cmd_run):
        self.cmd_build = cmd_build
        self.cmd_build_str = u' '.join(self.cmd_build)
        self.cmd_run = cmd_run
        self.cmd_run_str = u' '.join(self.cmd_run)

    def desc(self):
        return self.cmd_run_str

    def build(self):
        if self.cmd_build:
            print u'Executando', self.cmd_build_str
            if subprocess.call(self.cmd_build) < 0:
                print u'Compilação', self.cmd_build_str, u'falhou. IGNORANDO', self.cmd_run_str
                return False
        return True
    
    def create_program(self, params=[]):
        def program():
            return exec_program(self.cmd_run + params)
        return program

def load_cases(path, in_ext, exp_ext=DEFAULT_FILE_EXP_EXT):
    def has_in_ext(path):
        return os.path.isfile(path) and path.endswith(in_ext)
    return [Case(input, replace_ext(input, exp_ext))
                for input in sorted(find_files(path, has_in_ext))]

def load_progs_info(path, run_params=[],
                          prog_build=DEFAULT_PROG_BUILD,
                          prog_run=DEFAULT_PROG_RUN):
    def is_prog_run(path):
        return path.endswith(prog_run) and is_executable(path)
    def get_build_cmd(run):
        build = run[:-len(prog_run)] + prog_build
        return [build] if is_executable(build) else []
    return [ProgramInfo(get_build_cmd(run), [run] + run_params)
                for run in sorted(find_files(path, is_prog_run))]


# utilities
def is_executable(path):
    return os.path.isfile(path) and os.access(path, os.X_OK)

def find_files(path, filter):
    files = []
    for dirpath, _, _files in os.walk(path):
        for f in _files:
            f = os.path.join(dirpath, f)
            if filter(f):
                files.append(f)
    return files

def replace_ext(path, new_ext):
    base, _ = os.path.splitext(path)
    return base + new_ext
