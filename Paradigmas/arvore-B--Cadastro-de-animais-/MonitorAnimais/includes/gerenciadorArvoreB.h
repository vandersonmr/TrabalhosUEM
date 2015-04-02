#ifndef GERENCIADORARVOREB_H
#define GERENCIADORARVOREB_H
#include "arvoreB.h"
#include "listaDeRegistrosWorstFit.h"
#include "pilhaRegistros.h"
#include <string>

#define PROMOTION 0
#define NO_PROMOTION 1
#define ERRO -1
using namespace std;

struct insertReturn{
        int status;
        int promo_r_child;
        int promo_key;
	int promo_offset;
	BTPage* newPage;
};

class gerenciadorArvoreB{
private:
	int root;
	pilhaRegistros* PED;
	fileIO* io;	
	void split(int,int,BTPage*,insertReturn*,BTPage*);	
	void insertReg(BTPage*,int);
	insertReturn* insere(int,int,int,insertReturn*);
public:
	int posR=0;
	gerenciadorArvoreB(pilhaRegistros* p)
			{ PED = p; };
	int buscarRecursivamente(int,int);
	void restore(BTPage*,int,int);
	void move_right(BTPage*,int,int);
	void move_left(BTPage*,int,int);
	void combine(BTPage*,int,int);
	void driver(int,int);
	bool openArvore(string);
	void checkRoot();
	int buscar(int);
	int remove(int,int);
	void printTree(int,fileIO*,int*);
	int getRoot(){ return root; }
	BTPage* loadPTPage(int);
};
#endif
