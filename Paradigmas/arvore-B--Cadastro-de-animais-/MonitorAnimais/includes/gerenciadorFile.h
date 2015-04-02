#ifndef GERENCIADORFILE_H
#define GERENCIADORFILE_H
#include "fileIO.h"

template<class Data>
class gerenciadorFile{
protected: 	
	fileIO* io;
public:
	virtual bool openFile(string){ return false; };
	virtual bool insere(Data){ return false; };
	virtual int busca(Data*){ return -1; };
	virtual bool remove(Data){ return false; };
	virtual void close(){};
};

#endif
