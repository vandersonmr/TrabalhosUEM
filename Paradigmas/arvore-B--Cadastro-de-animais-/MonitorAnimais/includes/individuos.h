#ifndef INDIVIDUOS_H
#define INDVIDUOS_H

class individuos{
private:
	int especie;
	int indentificador;
	char sexo;
public:
	individuos(int e,int i, char s){setEspecie(e);
					setIndentificador(i);
					setSexo(s);
					};
	void setEspecie(int e){ especie = e; };                                       
	void setIndentificador(int i){ indentificador = i; };
	void setSexo(char s){ sexo = s; };
	int getEspecie(){ return especie; };
	int getIndentificador(){ return indentificador; };
	char getSexo(){ return sexo; };
};

#endif
