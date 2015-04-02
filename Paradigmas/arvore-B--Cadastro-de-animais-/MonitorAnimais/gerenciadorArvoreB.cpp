#include "includes/gerenciadorArvoreB.h"
#include "includes/fileIO.h"
#include "includes/listaDeRegistrosWorstFit.h"
#include <string>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

bool gerenciadorArvoreB::openArvore(string name){
	io = new fileIO();
	bool res = io->openFile(string(name));	
	fileIO* IO = new fileIO();
        IO->openFile(string("./data/root"));
	string line = IO->readPos(0,6);
	root = atoi(line.c_str());
	delete IO;
	return res;
}

int gerenciadorArvoreB::buscarRecursivamente(int chave,int RRN){	
	int size = PED->getSizeReg();
	int pos = 0;
	if(RRN == -1){
		return -1;	
	}else{
		BTPage* reg = loadPTPage(RRN);
		int i;
		for(i=0;i<reg->totalChaves;i++){
			if(reg->chaves[i]==chave){
				return reg->offset[i];
			}else if(reg->chaves[i] < chave){
				pos = reg->filha[i+1];
			}else{
				pos = reg->filha[i];
				break;			
			}
		}
		posR = pos;
		return	buscarRecursivamente(chave,pos);
	}
}

int gerenciadorArvoreB::buscar(int chave){
	if(PED->getNumRegs() > 0){
		return buscarRecursivamente(chave, root);
	}else{
		return -1;
	}
}


void gerenciadorArvoreB::split(int key, int offset, BTPage* reg, insertReturn* result, BTPage* newReg){	
	BTPage* aux = new BTPage(6);
	int i;
	for(i=0;i<reg->totalChaves;i++){
		int pos = aux->addChave(reg->chaves[i],reg->offset[i]);	
		aux->addFilha(reg->filha[i],pos);
		aux->addFilha(reg->filha[i+1],pos+1);
	}
	int pos = aux->addChave(key,offset);
	aux->addFilha(result->promo_r_child,pos+1);
	result->promo_key = aux->chaves[aux->totalChaves/2];
	result->promo_offset = aux->offset[aux->totalChaves/2];
	result->promo_r_child = PED->getPosToWriteNewReg();

	reg->setTotalChaves(0);
	for(i=0;i<aux->totalChaves/2;i++){
		int pos = reg->addChave(aux->chaves[i],aux->offset[i]);
		reg->addFilha(aux->filha[i],pos);
		reg->addFilha(aux->filha[i+1],pos+1);	
	}
	for(i=(aux->totalChaves/2)+1;i<aux->totalChaves;i++){
		int pos = newReg->addChave(aux->chaves[i],aux->offset[i]);
                newReg->addFilha(aux->filha[i],pos);       
                newReg->addFilha(aux->filha[i+1],pos+1);
	}
}

void gerenciadorArvoreB::insertReg(BTPage* reg,int RRN){
	int pos = RRN;
	if(pos >= PED->getPosToWriteNewReg()){
        	PED->setNumRegs(PED->getNumRegs()+1);
	}

        stringstream BTPageRaw;
        BTPageRaw << reg->totalChaves << "|" <<
                reg->filha[0] << "|" << reg->chaves[0] <<
		"|" << reg->offset[0] <<"|"<< reg->filha[1] <<
		"|" << reg->chaves[1] << "|" << reg->offset[1] 
		<< "|" << reg->filha[2] << "|" << reg->chaves[2] <<
                "|" << reg->offset[2] <<"|"<< reg->filha[3] <<
		"|" << reg->chaves[3] << "|" << reg->offset[3] 
		<<"|"<< reg->filha[4] << "#";

        if(BTPageRaw.str().size() < PED->getSizeReg()){
                io->writeAtPos(pos,BTPageRaw.str());
                return;
        }else{
                return;
        }

}

insertReturn* gerenciadorArvoreB::insere(int key,int offset,int RRN,insertReturn* result){

	int pos = 0;
	insertReturn* resval;	
	BTPage* reg;

	if(RRN == -1){
		result->promo_key = key;
		result->promo_offset = offset;
		result->promo_r_child = -1; 
		result->status = PROMOTION;	
		return result;
	}else{
		reg = loadPTPage(RRN);
		int i;
		for(i=0;i<reg->totalChaves;i++){
			if(reg->chaves[i]==key){
				result->status=ERRO;
				return result;
			}else if(reg->chaves[i] < key){
				pos = i+1;
			}else{
				pos = i;
				break;			
			}
		}
		resval = insere(key,offset,reg->filha[pos],result);
	}

	if(resval->status == NO_PROMOTION || resval->status == ERRO){
		return 	resval;
	}else{
		
		if(reg->totalChaves < (reg->D-1)){
			int pos = reg->addChave(result->promo_key,result->promo_offset);	
			reg->addFilha(result->promo_r_child,pos+1);
			result->status = NO_PROMOTION;
			insertReg(reg,RRN);
			return result;	
		}else{
			BTPage *newReg = new BTPage();
			split(result->promo_key,result->promo_offset,reg,result,newReg);
			insertReg(reg,RRN);
			insertReg(newReg,result->promo_r_child);
			result->status = PROMOTION;
			return result;
		}
	}
	delete reg;

}

void gerenciadorArvoreB::driver(int key,int offset){
	fileIO* IO = new fileIO();
	IO->openFile(string("./data/root"));
	stringstream rootRaw;
	if(PED->getNumRegs() == 0 ){
		BTPage* reg = new BTPage();
		reg->addChave(key,offset);
		insertReg(reg,0);
		root = 0;
	}else{
		root = atoi(IO->readPos(0,6).c_str());	
		insertReturn* result = (insertReturn*) malloc(sizeof(insertReturn));
		if(insere(key,offset,root,result)->status == PROMOTION){
			BTPage* reg = new BTPage();
			reg->addChave(result->promo_key,result->promo_offset);
			reg->addFilha(root,0);
			reg->addFilha(result->promo_r_child,1);
			int RRN = PED->getPosToWriteNewReg();
			root = 	RRN;
			insertReg(reg,RRN);
		}	
	}
	rootRaw << root << setfill(' ') << setw(3);	
	IO->writeAtPos(0,rootRaw.str());
	delete IO;
}

int gerenciadorArvoreB::remove(int RRN,int chave){
	BTPage* reg = loadPTPage(RRN);
	int i,pos,res;
	int u=reg->totalChaves;
	while( u > 0 && chave < reg->chaves[u-1]){
		u--;	
	}

	for(i=0;i<reg->totalChaves;i++){
                if(reg->chaves[i]==chave){
			pos = reg->filha[i];
			break;
                }else if(reg->chaves[i] < chave){
                        pos = reg->filha[i+1];
                }else{
                        pos = reg->filha[i];
        	        break;
	        }
        }

	if(reg->chaves[i] != chave){
		if(pos!=-1){
			res= remove(pos,chave);
		}else{
			res= 0;
		}
	}else{
		if(pos==-1){
			reg->removeChave(chave);
			insertReg(reg,RRN);		
		}else{
			int posB = reg->filha[i+1];
			BTPage* aux;
			int posA;
			while (posB != -1){
				posA = posB; 
				aux = loadPTPage(posB);
				posB = aux->filha[0];	
			}
				
			reg->chaves[i] = aux->chaves[0];
			reg->offset[i] = aux->offset[0];
			insertReg(reg,RRN);
			remove(reg->filha[i+1],aux->chaves[0]);
		}
	
	}
	if(pos!=-1){
		BTPage* aux = loadPTPage(reg->filha[u]);
		if(aux->getTotalChaves() <= ((aux->D/2) - 1)){
			restore(reg,u,RRN);	
		}
	}
	return res;
}

void gerenciadorArvoreB::restore(BTPage* reg,int i,int RRN){
	if( i == reg->getTotalChaves()){
		BTPage* aux = loadPTPage(reg->filha[i-1]);
		if(aux->getTotalChaves() > ((aux->D/2))){	
			move_right(reg,i-1,RRN);	
		}else{
			combine(reg,i,RRN);	
		}		
	}else{
		if(i==0){
			BTPage* aux = loadPTPage(reg->filha[1]);
			if(aux->getTotalChaves() > ((aux->D/2))){
				move_left(reg,1,RRN);
			}else{			
				combine(reg,1,RRN);
			}
		}else{
			BTPage* aux = loadPTPage(reg->filha[i-1]);
			if(aux->getTotalChaves() > ((aux->D/2))){
				move_right(reg,i-1,RRN);
			}else{
				aux = loadPTPage(reg->filha[i+1]);	
 				if(aux->getTotalChaves() > ((aux->D/2))){
					move_left(reg,i+1,RRN);
				}else{
					combine(reg,i,RRN);
				}
				
			}
		}
	}	
}

void gerenciadorArvoreB::move_right(BTPage* reg,int i,int RRN){	
	BTPage* right = loadPTPage(reg->filha[i+1]);
	BTPage* left = loadPTPage(reg->filha[i]);
	
	int  lc = left->chaves[left->getTotalChaves()-1];
	int lo = left->offset[left->getTotalChaves()-1];
	int lf = left->filha[left->getTotalChaves()];
	
	int pos = right->addChave(reg->chaves[i],reg->offset[i]);
	right->addFilha(lf,pos);
	left->totalChaves -= 1;

	reg->chaves[i]=lc;
	reg->offset[i]=lo;

	insertReg(right,reg->filha[i+1]);
	insertReg(left,reg->filha[i]);
	insertReg(reg,RRN);
}

void gerenciadorArvoreB::move_left(BTPage* reg,int i, int RRN){
	BTPage* right = loadPTPage(reg->filha[i]);
	BTPage* left = loadPTPage(reg->filha[i-1]);	
	
	int rc = right->chaves[0];
	int ro = right->offset[0];
	int rf = right->filha[0];
	
	right->removeChave(rc);
	int pos = left->addChave(reg->chaves[i-1],reg->offset[i-1]);
	left->filha[pos+1]=rf;

	reg->chaves[i-1]=rc;
	reg->offset[i-1]=ro;

	insertReg(reg,RRN);
	insertReg(right,reg->filha[i]);
	insertReg(left,reg->filha[i-1]);	
}
	
void gerenciadorArvoreB::combine(BTPage* reg,int i,int RRN){
	BTPage* right = loadPTPage(reg->filha[i]);
        BTPage* left = loadPTPage(reg->filha[i-1]);	
	int pos = left->addChave(reg->chaves[i-1],reg->offset[i-1]);
	reg->removeChave(reg->chaves[i-1]);
	left->filha[pos+1]=right->filha[0];
	int j;
	for(j=0;j<right->totalChaves;j++){
		int pos = left->addChave(right->chaves[j],right->offset[j]);
		left->addFilha(right->filha[j+1],pos+1);
	}

        insertReg(reg,RRN);
        insertReg(left,reg->filha[i-1]);

}

void gerenciadorArvoreB::checkRoot(){
	BTPage* rootp =  loadPTPage(root);
	if(rootp->getTotalChaves() == 0){
		root = rootp->filha[0];
	}
}

BTPage* gerenciadorArvoreB::loadPTPage(int addr){
	BTPage* r = new BTPage();

	int size = PED->getSizeReg();
	int realAddr = addr;
	string reg = io->readPos(realAddr,size);
	sscanf(reg.c_str(),"%hd|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d#",&r->totalChaves,
	&r->filha[0],&r->chaves[0],&r->offset[0],&r->filha[1],&r->chaves[1],&r->offset[1],&r->filha[2],&r->chaves[2],&r->offset[2],&r->filha[3],
	&r->chaves[3],&r->offset[3],&r->filha[4]);

	return r;
}

void gerenciadorArvoreB::printTree(int RRN,fileIO* io,int* pos){
	if(RRN!=-1){
		BTPage* reg = loadPTPage(RRN);
		stringstream regRaw;
		if(RRN==root){
			regRaw << "\n--- ROOT ---";
		}else{
			regRaw << "\n------------";
		}
		regRaw << "\nRRN: " << RRN/PED->getSizeReg() << "\n";
		regRaw << "Chaves: ";
		int i;
		for(i=0;i<reg->getTotalChaves();i++){
                        regRaw << reg->chaves[i] << " | ";
                }
		regRaw << "\nOffsets: ";
		for(i=0;i<reg->getTotalChaves();i++){
                        regRaw << reg->offset[i] << " | ";
                } 
                regRaw << "\nFilhas: ";
                for(i=0;i<=reg->getTotalChaves();i++){
			if(reg->filha[i] == -1){
				regRaw << "-1 | ";
			}else{
                        	regRaw << reg->filha[i]/PED->getSizeReg() << " | ";
                	}
		}
		regRaw << "\n\n";
		int size = regRaw.str().size();
		io->writeAtPos(*pos,regRaw.str().c_str());

		for(i=0;i<=reg->getTotalChaves();i++){
			(*pos) = (*pos) + size;
			printTree(reg->filha[i],io,pos);
		}
	}	
}

