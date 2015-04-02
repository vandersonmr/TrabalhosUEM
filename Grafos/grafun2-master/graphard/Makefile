PYTHON=python2.7 -B

.PHONY: testar testar-ec testar-tsp

testar:
	@rm -f testes.log
	@echo "** Testando todos **"
	@for alg in ec tsp-nn tsp-mst tsp-nn-2opt tsp-mst-2opt; do\
		$(PYTHON) testador/main.py testes/ src/ $$alg; done

testar-ec:
	@rm -f testes.log
	@echo "** Testando ec **"
	@$(PYTHON) testador/main.py testes/ src/ ec

testar-tsp:
	@rm -f testes.log
	@echo "** Testando tsp **"
	@for alg in tsp-nn tsp-mst tsp-nn-2opt tsp-mst-2opt; do\
		$(PYTHON) testador/main.py testes/ src/ $$alg; done

atualizar:
	@git pull

zip: src.zip

src.zip: $(shell find src/ -type f ! -path 'src/*/target/*' ! -name '*~')
	@if grep -q -P '\000' $?; then\
        echo "** Arquivos binários encontrados **";\
        grep -l -P '\000' $?;\
        echo "** Remova os arquivos binários antes de fazer o envio **";\
        echo "** Se você estiver usando um IDE, procure pela opção Clean **";\
        exit 1; fi
	@echo Criando arquivo src.zip.
	@zip --quiet src.zip -r $?
	@echo Arquivo src.zip criado.

enviar: src.zip
	@$(PYTHON) enviar.py src.zip

limpar-log:
	@echo Removendo arquivos de log
	@rm *.log

limpar: limpar-log
	@echo Removendo src.zip
	@rm -f src.zip

limpar-target:
	@rm -rf $$(find src/ -path 'src/*/target')
