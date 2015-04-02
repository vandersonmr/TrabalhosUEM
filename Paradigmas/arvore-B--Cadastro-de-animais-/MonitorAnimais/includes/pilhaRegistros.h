#ifndef PILHAREGISTROS_H
#define PILHAREGISTROS_H
#include "fileIO.h"

class pilhaRegistros{
private:
	int numRegs = 0;
	int numRegsDeletados = 0;
	int tamanhoRegs = 0;
	int PED = -1;
public:
	int getPosToWriteNewReg(){ return PED==-1?tamanhoRegs*(numRegs+numRegsDeletados):PED; };
	void loadHead(fileIO*);
	int getSizeReg() { return tamanhoRegs; };
	void commitHead(fileIO*);
	void setNumRegs(int n){ numRegs = n; };
	void setTamanhoRegs(int n){ tamanhoRegs = n; };
	int getNumRegs(){ return numRegs; };
	int getPED(){return PED;};
	void setPED(int p){PED=p;};
	void setNumRegsDeletados(int v){numRegsDeletados = v; };
	int getNumRegsDeletados(){ return numRegsDeletados;};
};
	
#endif
