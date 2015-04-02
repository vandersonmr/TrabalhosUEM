#include "includes/gerenciadorCapturas.h"
#include "includes/fileIO.h"
#include "includes/listaDeRegistrosWorstFit.h"
#include <string>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>


bool gerenciadorCapturas::openFile(string name){
	io = new fileIO();
	return io->openFile(string(name));	
}

bool gerenciadorCapturas::insere(capturas captura){
	stringstream capturaRaw, aux;

	capturaRaw << captura.getId() << "|" <<captura.getIdIndividuo() << "|"
	   << captura.getComprimento()  << "|" << captura.getLargura() << "|" 
	   << captura.getPeso() << "|" << captura.getData() << "|" 
	   << captura.getLocal()  << "#"; 

	int size = capturaRaw.str().size(); 

	if(LED->getLED() == -1){

		int posFimArquivo = LED->getPosFimArquivo();

		aux << size << "*" << capturaRaw.str();

		io->writeAtPos(posFimArquivo,aux.str());

		LED->setPosFimArquivo(aux.str().size() + posFimArquivo);
	
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
								

				aux << size << "*" << capturaRaw.str() << setfill(' ') << setw(3) << sobra << "*" 
						<< next << "@";

				stringstream auxt;
				auxt << size << "*";
				io->writeAtPos(pos,aux.str());
				LED->setLED(pos+size+auxt.str().size());

				
				return true;

			}

			pos = next;
			
		}

		int posFimArquivo = LED->getPosFimArquivo();

		aux << size << "*" << capturaRaw.str();

		io->writeAtPos(posFimArquivo,aux.str());

		LED->setPosFimArquivo(aux.str().size() + posFimArquivo);
	
		return true;   

	}	

	
}

int gerenciadorCapturas::busca(capturas* captura){
	int posFimArquivo = LED->getPosFimArquivo();
	int pos = 0;
	
	while(posFimArquivo > 0){
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
	
		int length;
		if(reg.find('@',0) == -1){
			int id;
			int idInd;
			int c;
			int l;
			int p;
			char d[15];
			char lc[100];
			sscanf(reg.c_str(),"%d*%d|%d|%d|%d|%d|%[^|]|%[^#|]",&length,&id,&idInd,&c,
								&l,&p,d,lc);
			if(id == captura->getId()){
				captura->setId(id);
				captura->setIdIndividuo(idInd);
				captura->setComprimento(c);
				captura->setLargura(l);
				captura->setPeso(p);
				captura->setData(string(d));
				captura->setLocal(string(lc));
				captura->setSize(size);
	
				return pos;
			}
		}


		// Atualiza pos
		pos += tamanhoReal;
		posFimArquivo -= tamanhoReal;
		
		
	}

	return -1;
}

list<capturas> gerenciadorCapturas::getListaCapturaPorIndividuo(int idIndividuo){
	int posFimArquivo = LED->getPosFimArquivo();
	int pos = 0;
	list<capturas> listaDeCapturas;	

	while(posFimArquivo > 0){
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
		
		int length;
		if(reg.find('@',0) == -1){
			int id;
			int idInd;
			int c;
			int l;
			int p;
			char d[15];
			char lc[100];
			sscanf(reg.c_str(),"%d*%d|%d|%d|%d|%d|%[^|]|%[^#|]",&length,&id,&idInd,&c,
								&l,&p,d,lc);
			if(idIndividuo == idInd){
				capturas captura(id,idInd,c,l,p,string(d),string(lc));
	
				listaDeCapturas.push_back(captura);
			}
		}


		// Atualiza pos
		pos += tamanhoReal;
		posFimArquivo -= tamanhoReal;
		
		
	}

	return listaDeCapturas;
} 

bool gerenciadorCapturas::remove(capturas captura){
	int pos = busca(&captura);
	stringstream addr;

	if(pos != -1){  //Existe o registro
		int size = captura.getSize();
		addr << size << "*" << LED->getLED() << "@";		
		io->writeAtPos(pos,addr.str());
		LED->setLED(pos);
		return true;
	}		

	return false;
}

void gerenciadorCapturas::close(){
	io->closeFile();
	delete this;
}


