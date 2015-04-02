#include "includes/gerenciadorIndividuos.h"
#include "includes/fileIO.h"
#include "includes/pilhaRegistros.h"
#include <sstream>
#include <cstdio>


bool gerenciadorIndividuos::openFile(string name){
	io = new fileIO();
	return io->openFile(string(name));	
}

bool gerenciadorIndividuos::insere(individuos individuo){
	int pos = PED->getPosToWriteNewReg();
	PED->setNumRegs(PED->getNumRegs()+1);

	stringstream individuoRaw;
	individuoRaw << individuo.getIndentificador() << "|" << 
		individuo.getEspecie() << "|" << individuo.getSexo() 
		<< "#";
	
	if(individuoRaw.str().size() < PED->getSizeReg()){
		if(PED->getPED() != -1){
			string reg = io->readPos(pos,PED->getSizeReg());
			int pointer = -1;
			char * rubish;
			sscanf(reg.c_str(),"%d*%s",&pointer,rubish);
			PED->setPED(pointer);
			PED->setNumRegsDeletados(PED->getNumRegsDeletados()-1);		
		}
	
		io->writeAtPos(pos,individuoRaw.str());
		return true;
	}else{
		return false;
	}
	
}

int gerenciadorIndividuos::busca(individuos* individuo){
	int size = PED->getSizeReg();
	int num = PED->getNumRegs();
        int numDeletados = PED->getNumRegsDeletados();
	
	for(int i = 0; i < num + numDeletados; i++){
		string reg = io->readPos(i*size,size);
		
		if(reg.find('*',0) == -1){
			int i1,i2;
			char sex;
		
			sscanf(reg.c_str(),"%d|%d|%c#",&i1,&i2,&sex);
		
			if(individuo->getIndentificador() == i1){
				individuo->setIndentificador(i1);
				individuo->setEspecie(i2);
				individuo->setSexo(sex);
				return i*size;
			}
		}
	}
	return -1;
}

list<int> gerenciadorIndividuos::getListaDeIndividuosDeUmaEspecie(int idEspecie){
	list<int> listaIndividuos;
	int size = PED->getSizeReg();
	int num = PED->getNumRegs();
        int numDeletados = PED->getNumRegsDeletados();
	
	for(int i = 0; i < num + numDeletados; i++){
		string reg = io->readPos(i*size,size);
		cout << reg <<  endl;
		if(reg.find('*',0) == -1){
			int i1,i2;
			char sex;
		
			sscanf(reg.c_str(),"%d|%d|%c#",&i1,&i2,&sex);
		
			if(idEspecie == i2){
				
				listaIndividuos.push_back(i1);
			}
		}
	}
	return listaIndividuos;
}

bool gerenciadorIndividuos::remove(individuos individuo){
	int pos = busca(&individuo);
	stringstream addr;

	if(pos != -1){  //Existe o registro
		addr << PED->getPED() << "*"; 
		io->writeAtPos(pos,addr.str());
		PED->setPED(pos);
		PED->setNumRegs(PED->getNumRegs()-1);
		PED->setNumRegsDeletados(PED->getNumRegsDeletados()+1);
		return true;
	}
	return false;
}

void gerenciadorIndividuos::close(){
	io->closeFile();
	delete this;
}
