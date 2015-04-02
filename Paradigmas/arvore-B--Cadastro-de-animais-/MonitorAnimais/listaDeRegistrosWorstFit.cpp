#include "includes/listaDeRegistrosWorstFit.h"
#include <sstream>
#include <cstdio>
#include <iomanip>

void listaDeRegistrosWorstFit::commitHead(fileIO* io){
	stringstream HEAD;
	HEAD << posFimArquivo << "|" << setfill(' ') << setw(4) << LED ;

	io->writeAtPos(0,HEAD.str());
}

void listaDeRegistrosWorstFit::loadHead(fileIO* io){
	string res = io->readPos(0,20);
	sscanf(res.c_str(),"%d|%d",&posFimArquivo,&LED);
}
