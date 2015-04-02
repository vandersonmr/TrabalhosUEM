# encoding: utf-8

import sys
import os
import codecs
from progunitutils import *
from eccheck import eulerian_cycle_check_main
from tspcheck import tsp_check_main

sys.stdout = codecs.getwriter('utf-8')(sys.stdout)

CHECKERS = {
    'ec': eulerian_cycle_check_main,
    'tsp-nn': tsp_check_main,
    'tsp-mst': tsp_check_main,
    'tsp-nn-2opt': tsp_check_main,
    'tsp-mst-2opt': tsp_check_main,
}

class MyReporter(SimpleReporter):
    def __init__(self):
        SimpleReporter.__init__(self, u'testes.log')

    def _on_success(self, test_case, test_result):
        if u'tsp' in test_case.description:
            cust = test_result.program_result.out.splitlines()[0]
            time = test_result.program_result.time
            self._write(u'OK (custo: %s, tempo: %s)\n' % (cust, time_str(time)))
        else:
            time = test_result.program_result.time
            self._write(u'OK (tempo: %s)\n' % (time_str(time),))

def get_formatted_checkers():
    return '|'.join(sorted(c for c in CHECKERS))

def validade_progs(path, progs):
    if not progs:
        print u'Nenhum arquivo run executável encontrado em', path
        print u'Lembre-se de executar o comando "chmod -f +x src/lang/{run,build}"'
        print u'onde lang é a linguagens escolhida para implementar o trabalho.'
        sys.exit(1)

def validade_cases(path, cases):
    if not cases:
        print u'Nenhum arquivo de teste encontrado em', path 
        sys.exit(1)

def show_usage():
    print u'Modo de usar: %s cases-path progs-path %s' % (sys.argv[0], get_formatted_checkers())

def main():
    if len(sys.argv) != 4:
        print u'Número inválido de parâmetros'
        show_usage()
        sys.exit(1)
    cases_path, progs_path, alg = [x.decode('utf-8') for x in sys.argv[1:]]
    if alg not in CHECKERS:
        print u'Algoritmo inválido:', alg
        show_usage()
        sys.exit(1)
    if alg.startswith(u'tsp-'):
        cases_path = os.path.join(cases_path, u'tsp')
        ext = u'.tsp'
    else:
        cases_path = os.path.join(cases_path, alg)
        ext = u'.g'
    cases = load_cases(cases_path, in_ext=ext)
    validade_cases(cases_path, cases)
    progs = load_progs_info(progs_path, run_params = [alg])
    validade_progs(progs_path, progs)
    run_progs_cases(CHECKERS[alg], progs, cases, MyReporter())

if __name__ ==  '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print
        print u'Interrompido'
