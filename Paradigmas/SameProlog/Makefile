PYTHON=python2.7 -B

.PHONY: testar-pequenos testar-medios testar-grandes atualizar zip limpar limpar-log

testar-pequenos:
	@echo Executando testes pequenos
	@$(PYTHON) testador/testador.py src testes/pequenos

testar-medios:
	@echo Executando testes medios
	@$(PYTHON) testador/testador.py src testes/medios

testar-grandes:
	@echo Executando testes grandes
	@$(PYTHON) testador/testador.py src testes/grandes

plunit:
	@cd src/prolog/ && make testar

atualizar:
	git pull

zip: src.zip

src.zip: $(shell find src/ -type f ! -wholename 'src/racket/compiled*' ! -name '*~' ! -wholename 'src/racket/resame')
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

# TODO: criar make ajuda?
