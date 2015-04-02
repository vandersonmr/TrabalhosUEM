#include "includes/pilhaRegistros.h"
#include <sstream>
#include <cstdio>
#include <iomanip>

void pilhaRegistros::commitHead(fileIO* io){
	stringstream HEAD;
	HEAD << numRegs << "|" << numRegsDeletados << "|"<< 
			tamanhoRegs << "|"  << setfill(' ') << setw(3) << PED;
	io->writeAtPos(0,HEAD.str());
}

void pilhaRegistros::loadHead(fileIO* io){
	string res = io->readPos(0,50);
	sscanf(res.c_str(),"%d|%d|%d|%d",&numRegs,&numRegsDeletados,&tamanhoRegs,&PED);
}
