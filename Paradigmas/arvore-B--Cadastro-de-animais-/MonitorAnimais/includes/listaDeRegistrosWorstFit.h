#ifndef LISTADEREGISTROSWORSTFIT_H
#define LISTADEREGISTROSWORSTFIT_H
#include "fileIO.h"

class listaDeRegistrosWorstFit{
private:
	int posFimArquivo = 0;
	int LED = -1;
public:
	void loadHead(fileIO*);
	void commitHead(fileIO*);

	int getPosFimArquivo() { return posFimArquivo; };
	void setPosFimArquivo(int n){ posFimArquivo = n; };

	int getLED(){ return LED;};
	void setLED(int l){ LED = l;};

};
	
#endif
