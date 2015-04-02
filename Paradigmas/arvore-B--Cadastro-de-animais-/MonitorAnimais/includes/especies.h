#ifndef ESPECIES_H
#define ESPECIES_H
#include <string>
using namespace std;

class especies{
private:
	int idEspecie;
	string nomeCientifico;
	string nomePopular;
	string descricao;
	int size = -1;
public:
	especies(int id,string nc, string np, string d)
			{	
				setIdEspecie(id);
				setNomeCientifico(nc);
				setNomePopular(np);
				setDescricao(d);
			};
	void setIdEspecie(int id){ idEspecie = id; };
	void setNomeCientifico(string nc){ nomeCientifico = nc; };
	void setNomePopular(string np){ nomePopular = np;};
	void setDescricao(string d){ descricao = d;};
	void setSize(int s){ size = s;};

	int getSize(){ return size;};
	int getIdEspecie(){ return idEspecie;};
	string getNomeCientifico(){ return nomeCientifico; };
	string getNomePopular(){ return nomePopular; };
	string getDescricao(){ return descricao; };
};

#endif
