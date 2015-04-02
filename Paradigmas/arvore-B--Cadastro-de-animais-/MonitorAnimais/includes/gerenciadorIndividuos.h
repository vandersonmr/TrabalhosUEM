	#ifndef GERENCIADORINDIVIDUOS_H
#define GERENCIADORINDIVIDUOS_H
#include "individuos.h"
#include "gerenciadorFile.h"
#include "pilhaRegistros.h"
#include <list>

class gerenciadorIndividuos : public gerenciadorFile<individuos>{
private:
	pilhaRegistros* PED;
public:
	gerenciadorIndividuos(pilhaRegistros* p){ PED = p; };
	bool openFile(string);
        bool insere(individuos);
        int busca(individuos*);
	list<int> getListaDeIndividuosDeUmaEspecie(int);
        bool remove(individuos);
	void close();
};

#endif
