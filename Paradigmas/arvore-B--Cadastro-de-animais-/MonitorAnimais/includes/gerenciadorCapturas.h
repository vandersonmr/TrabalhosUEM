#ifndef GERENCIADORCAPTURAS_H
#define GERENCIADORCAPTURAS_H
#include "capturas.h"
#include "gerenciadorFile.h"
#include "listaDeRegistrosWorstFit.h"
#include <list>

class gerenciadorCapturas : public gerenciadorFile<capturas>{
private:
	listaDeRegistrosWorstFit* LED;
public:
	gerenciadorCapturas(listaDeRegistrosWorstFit* p)
				{ LED = p; };
	bool openFile(string);
        bool insere(capturas);
        int busca(capturas*);
	list<capturas> getListaCapturaPorIndividuo(int);
        bool remove(capturas);
	void close();
};

#endif
