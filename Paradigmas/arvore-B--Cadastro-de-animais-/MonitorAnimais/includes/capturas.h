#ifndef CAPTURAS_H
#define CAPTURAS_H
#include <string>
using namespace std;

class capturas{
private:
	int id;
	int idIndividuo;
	int comprimento;
	int largura;
	int peso;
	string data;
	string local;
	int size = -1;
public:
	capturas(int idc,int id,int c, int l, int p,string d, string local)
			{	
				setId(idc);
				setIdIndividuo(id);
				setComprimento(c);
				setLargura(l);
				setData(d);
				setPeso(p);
				setLocal(local);
			};

	void setSize(int s){ size = s;};
	int getSize(){ return size;};

	void setId(int i){ id = i;};
	int getId(){ return id; };

	void setIdIndividuo(int i){ idIndividuo = i;};
	int getIdIndividuo(){ return idIndividuo; };

	void setComprimento(int i){ comprimento = i;};
	int getComprimento(){ return comprimento; };

	void setLargura(int i){ largura = i;};
	int getLargura(){ return largura; };

	void setPeso(int i){ peso = i;};
	int getPeso(){ return peso; };
	
	void setData(string i){ data = i;};
	string getData(){ return data; };
	
	void setLocal(string i){ local = i;};
	string getLocal(){ return local; };
	
};

#endif
