#include "includes/gerenciadorEspecies.h"
#include "includes/fileIO.h"
#include "includes/listaDeRegistrosWorstFit.h"
#include <string>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

bool gerenciadorEspecies::openFile(string name){
	io = new fileIO();
	return io->openFile(string(name));	
}

bool gerenciadorEspecies::insere(especies especie){
	stringstream especieRaw, aux;

	especieRaw << especie.getIdEspecie() << "|" << especie.getNomeCientifico()
	   << "|" << especie.getNomePopular() << "|" << especie.getDescricao()
	   << "#";

	int size = especieRaw.str().size(); 

	if(LED->getLED() == -1){

		int posFimArquivo = LED->getPosFimArquivo();

		aux << size << "*" << especieRaw.str();

		io->writeAtPos(posFimArquivo,aux.str());

		LED->setPosFimArquivo(aux.str().size() + posFimArquivo);
	
		genArvoreB->driver(especie.getIdEspecie(),posFimArquivo);
		pedArvoreB->commitHead(ioHeadArvoreB);
		return true;   
               
	}else{	

		int pos = LED->getLED();

		while(pos != -1){
			string st = io->readPos(pos,9);
			char rubish[5];
			int len;
		 	int next;

			sscanf(st.c_str(),"%d*%d@%s",&len,&next,rubish);
			
			if((size+8) <= len){
				int sobra = len - size - 2;
				stringstream sobraRaw;

				sobraRaw << sobra;
				int sz = sobraRaw.str().size();

				sobraRaw << "*" << next << "@";
	

				aux << size << "*" << especieRaw.str() << setfill(' ') << setw(3) << sobra << "*" 
						<< next << "@";
				stringstream auxt;
				auxt << size << "*";
				io->writeAtPos(pos,aux.str());
				LED->setLED(pos+size+auxt.str().size());
				
				genArvoreB->driver(especie.getIdEspecie(),pos);
				pedArvoreB->commitHead(ioHeadArvoreB);
				return true;

			}

			pos = next;
			
		}

		int posFimArquivo = LED->getPosFimArquivo();

		aux << size << "*" << especieRaw.str();

		io->writeAtPos(posFimArquivo,aux.str());
		
		genArvoreB->driver(especie.getIdEspecie(),posFimArquivo);
		LED->setPosFimArquivo(aux.str().size() + posFimArquivo);
		pedArvoreB->commitHead(ioHeadArvoreB);		
		return true;   

	}	
}

void gerenciadorEspecies::printTree(string file){
	int aux = 0;
	int* pos = &aux;
	fileIO* ioa = new fileIO();
	ioa->openFileW(file);
	genArvoreB->printTree(genArvoreB->getRoot(),ioa,pos);
}

int gerenciadorEspecies::busca(especies* especie){
	int posFimArquivo = LED->getPosFimArquivo();
	int pos = genArvoreB->buscar(especie->getIdEspecie());
	if(pos < posFimArquivo && pos != -1){
		// Carrega tamanho do registro		
		string st = io->readPos(pos,5);
		
		char rubish[5];
		int size;
		 
		sscanf(st.c_str(),"%d*%s",&size,rubish);

		stringstream ss;
   		ss << size;
		
		int tamanhoReal = size 
			+ (ss.str().size()+1);

		// Lê registro inteiro
		string reg = io->readPos(pos,tamanhoReal);
	
		if(reg.find('@',0) == -1){	
			int length;		
			int id;
			char nc[size];
			char np[size];
			char d[size];
			sscanf(reg.c_str(),"%d*%d|%[^|]|%[^|]|%[^|]",&length,&id,nc,
								np,d);
			if(id == especie->getIdEspecie()){
				especie->setIdEspecie(id);
				especie->setNomeCientifico(string(nc));
				especie->setNomePopular(string(np));
				especie->setDescricao(string(d));
				especie->setSize(size);
	
				return pos;
			}
		}
	}

	return -1;
}

bool gerenciadorEspecies::remove(especies especie){
	int pos = busca(&especie);
	stringstream addr;

	if(pos != -1){  //Existe o registro
		int size = especie.getSize();
		addr << size << "*" << LED->getLED() << "@";		
		io->writeAtPos(pos,addr.str());
		LED->setLED(pos);

		genArvoreB->remove(genArvoreB->getRoot(),especie.getIdEspecie());
		genArvoreB->checkRoot();
		return true;
	}		

	return false;
}

void gerenciadorEspecies::close(){
	io->closeFile();
	delete this;
}


