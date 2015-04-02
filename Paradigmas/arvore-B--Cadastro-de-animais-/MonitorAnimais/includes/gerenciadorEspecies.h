#ifndef GERENCIADORESPECIES_H
#define GERENCIADORESPECIES_H
#include "especies.h"
#include "gerenciadorFile.h"
#include "listaDeRegistrosWorstFit.h"
#include "gerenciadorArvoreB.h"

class gerenciadorEspecies : public gerenciadorFile<especies>{
private:	
	fileIO* ioHeadArvoreB;
	pilhaRegistros* pedArvoreB;				
	 gerenciadorArvoreB* genArvoreB;
	listaDeRegistrosWorstFit* LED;
public:
	gerenciadorEspecies(listaDeRegistrosWorstFit* p)
				{ 
					LED = p; 
					ioHeadArvoreB = new fileIO();
					ioHeadArvoreB->openFile(string("./data/headArvoreB"));
					pedArvoreB = new pilhaRegistros();
					pedArvoreB->loadHead(ioHeadArvoreB);
					genArvoreB = new gerenciadorArvoreB(pedArvoreB);
					genArvoreB->openArvore("./data/arvoreB");
				};
	void printTree(string);
	bool openFile(string);
        bool insere(especies);
        int busca(especies*);
        bool remove(especies);
	void close();
};

#endif
