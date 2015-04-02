#include "includes/gerenciadorCapturas.h"  
#include "includes/gerenciadorEspecies.h"  
#include "includes/capturas.h"
#include "includes/gerenciadorIndividuos.h"                                  
#include "includes/fileIO.h"     
#include "includes/listaDeRegistrosWorstFit.h"                                               
#include "includes/pilhaRegistros.h"
#include "stdlib.h"
#include <cstring>
#include <iterator>


fileIO* ioHeadIndividuos;
pilhaRegistros* pedIndividuos;
gerenciadorIndividuos* gerenIndividuos;

fileIO* ioHeadEspecies;
listaDeRegistrosWorstFit* ledEspecies;
gerenciadorEspecies* gerenEspecies;

fileIO* ioHeadCapturas;
listaDeRegistrosWorstFit* ledCapturas;
gerenciadorCapturas* gerenCapturas;
               
void clear(){
	system("clear");
}

void menuRemoveIndividuo(){
	int id = -1;
	
	clear();
	cout << "Digite o id do indivíduo a ser removido: ";
	scanf("%d",&id);
	individuos individuo(-1,id,-1);

	bool removeu = gerenIndividuos->remove(individuo);

	clear();
	if(removeu){
		cout << "Remoção efetuado com sucesso!" << endl;
	}else{
		cout << "Registro não encontrado!" << endl;	
	}
	getchar();
	getchar();
	clear();
}

void menuBuscaIndividuo(){
	int id = -1;
	
	clear();
	cout << "Digite o id do indivíduo a ser buscado: ";
	scanf("%d",&id);
	individuos* individuo = new individuos(-1,id,-1);
	int encontrou = gerenIndividuos->busca(individuo);
	if(encontrou != -1){
		clear();
		cout << "Encontrado." << endl;
		cout << "Id: " << id << endl;
	        cout << "Espécie: " << individuo->getEspecie() << endl;
		cout << "Sexo: " << individuo->getSexo() << endl;
		cout << "Enter para continuar." << endl;
	}else{
		clear();
		cout << "Nenhum registro encontrado." << endl;
	}
	getchar();
	getchar();
	clear();
}

void menuInsereIndividuo(){
	clear();
	int idEspecie;	
	int id;
	char sexo;

	cout << "Inserir novo indivíduo:" << endl;
	cout << "Digite id da espécie: ";
	scanf("%d",&idEspecie);
	cout << "Digite o id:";
	scanf("%d",&id);
	cout << "Digite o sexo (m/f): ";
	scanf("%c %c",&sexo,&sexo);
	especies especie(idEspecie,string(""),string(""),string(""));
	if(gerenEspecies->busca(&especie) != -1){
		individuos individuo(idEspecie,id,sexo);
		if(gerenIndividuos->busca(&individuo) == -1){
			gerenIndividuos->insere(individuo);
		}else{
			cout << "ID do indivíduo já cadastrado." << endl;
			getchar();
		}
	}else{
		cout << "Espécie não existe!" << endl;
		getchar();
		getchar();
	
	}
	
	clear();	
}

void menuRemoveEspecie(){
	int id = -1;
	
	clear();
	cout << "Digite o id do espécie a ser removido: ";
	scanf("%d",&id);
	especies especie(id,"","","");

	bool removeu = gerenEspecies->remove(especie);

	clear();
	if(removeu){
		cout << "Remoção efetuado com sucesso!" << endl;
	}else{
		cout << "Registro não encontrado!" << endl;	
	}
	getchar();
	getchar();
	clear();
}

void menuBuscaEspecie(){
	int id = -1;
	
	clear();
	cout << "Digite o id da espécie a ser buscada: ";
	scanf("%d",&id);
	especies* especie = new especies(id,"","","");
	int encontrou = gerenEspecies->busca(especie);
	if(encontrou != -1){
		clear();
		cout << "Encontrado." << endl;
		cout << "Id: " << id << endl;
	        cout << "Nome Científico: " << especie->getNomeCientifico() << endl;
		cout << "Nome Popular: " << especie->getNomePopular() << endl;
		cout << "Descrição: " << especie->getDescricao() << endl;
		cout << "Enter para continuar." << endl;
	}else{
		clear();
		cout << "Nenhum registro encontrado." << endl;
	}
	getchar();
	getchar();
	clear();
}

void menuInsereEspecie(){
	clear();
	int id;
	string nomeCientifico;
	string nomePopular;
	string descricao;

	cout << "Inserir nova espécie:" << endl;
	cout << "Digite id: ";
	scanf("%d",&id);
	cout << "Digite o nome científico:";
	getchar();
	getline(cin, nomeCientifico, '\n'); 
	cout << "Digite o nome popular:";
	getline(cin, nomePopular, '\n');  
	cout << "Digite uma descrição: ";
	getline(cin, descricao, '\n');  
	
	especies especie(id,nomeCientifico,nomePopular,descricao);
	if(gerenEspecies->busca(&especie) == -1){
		gerenEspecies->insere(especie);
	}else{
		cout << "Espécie já cadastrada" << endl; 
		getchar();
		getchar();	
	}
	
	clear();	
}

void menuRemoveCaptura(){
	int id = -1;
	
	clear();
	cout << "Digite o id da captura a ser removido: ";
	scanf("%d",&id);
	capturas captura(id,id,0,0,0,string(""),string(""));

	bool removeu = gerenCapturas->remove(captura);

	clear();
	if(removeu){
		cout << "Remoção efetuado com sucesso!" << endl;
	}else{
		cout << "Registro não encontrado!" << endl;	
	}
	getchar();
	getchar();
	clear();
}

void menuBuscaCaptura(){
	int id = -1;
	
	clear();
	cout << "Digite o id da captura a ser buscada: ";
	scanf("%d",&id);
	capturas* captura = new capturas(id,id,0,0,0,string(""),string(""));
	int encontrou = gerenCapturas->busca(captura);
	if(encontrou != -1){
		clear();
		cout << "Encontrado." << endl;
		cout << "Id: " << id << endl;
		cout << "Id indivíduo: " << captura->getIdIndividuo() << endl;
	        cout << "Comprimento: " << captura->getComprimento() << endl;
		cout << "Largura: " << captura->getLargura() << endl;
		cout << "Peso: " << captura->getPeso() << endl;
		cout << "Data: " << captura->getData() << endl;
		cout << "Local: " << captura->getLocal() << endl;
		cout << "Enter para continuar." << endl;
	}else{
		clear();
		cout << "Nenhum registro encontrado." << endl;
	}
	getchar();
	getchar();
	clear();
}

void menuInsereCaptura(){
	clear();
	int id;
	int idInd;
	int c;
	int l;
	int p;
	string d;
	string local;
	
	cout << "Inserir nova captura:" << endl;
	cout << "Digite id: ";
	scanf("%d",&id);
	cout << "Digite id do indivíduo: ";
	scanf("%d",&idInd);
	cout << "Digite o comprimento:";
	scanf("%d",&c);
	cout << "Digite a largura:";
	scanf("%d",&l);	
	cout << "Digite o peso: ";
	scanf("%d",&p);
	cout << "Digite a data: ";
	getchar();
	getline(cin, d, '\n'); 
	cout << "Digite o local: ";
	getline(cin, local, '\n'); 
	
	
	capturas captura(id,idInd,c,l,p,d,local);
	if(gerenCapturas->busca(&captura) == -1){
		gerenCapturas->insere(captura);
	}else{
		cout << "Já existe esse ID" << endl;	
		getchar();
		getchar();	
	}
	
	clear();	
}

void menuIndividuos(){
	clear();
	cout << "Gerenciador indivíduos. Escolha uma das opções:" << endl;
	cout << "	1 - inserir indivíduo" << endl;
	cout << "	2 - buscar indivíduo por id" << endl;
	cout << "	3 - remover indivíduo por id" << endl;
	cout << "	4 - sair" << endl;
	cout << "escolha uma opção: ";
	int op;
	scanf("%d",&op);
	if(op == 1){
		menuInsereIndividuo();		
	}else if(op == 2){
		menuBuscaIndividuo();
	}else if(op == 3){
		menuRemoveIndividuo();	
	}
	clear();
}

void menuEspecies(){
	clear();
	cout << "Gerenciador espécies. Escolha uma das opções:" << endl;
	cout << "	1 - inserir espécie" << endl;
	cout << "	2 - buscar espécie por id" << endl;
	cout << "	3 - remover espécie por id" << endl;
	cout << "	4 - sair" << endl;
	cout << "escolha uma opção: ";
	int op;
	scanf("%d",&op);
	if(op == 1){
		menuInsereEspecie();		
	}else if(op == 2){
		menuBuscaEspecie();
	}else if(op == 3){
		menuRemoveEspecie();	
	}
	clear();
}

void menuCapturas(){
	clear();
	cout << "Gerenciador capturas. Escolha uma das opções:" << endl;
	cout << "	1 - inserir captura" << endl;
	cout << "	2 - buscar captura por id" << endl;
	cout << "	3 - remover captura por id" << endl;
	cout << "	4 - sair" << endl;
	cout << "escolha uma opção: ";
	int op;
	scanf("%d",&op);
	if(op == 1){
		menuInsereCaptura();		
	}else if(op == 2){
		menuBuscaCaptura();
	}else if(op == 3){
		menuRemoveCaptura();	
	}
	clear();
}


void geraHistoricoIndividuo(int id){
	list<capturas> lista = gerenCapturas->getListaCapturaPorIndividuo(id);

	list<capturas>::iterator itCaptura;
	
	for(itCaptura = lista.begin(); 
     		itCaptura != lista.end();
       		itCaptura++){
		
		capturas* captura = &(*itCaptura);

		cout << "Encontrado." << endl;
		cout << "Id: " << id << endl;
		cout << "Id indivíduo: " << captura->getIdIndividuo() << endl;
	        cout << "Comprimento: " << captura->getComprimento() << endl;
		cout << "Largura: " << captura->getLargura() << endl;
		cout << "Peso: " << captura->getPeso() << endl;
		cout << "Data: " << captura->getData() << endl;
		cout << "Local: " << captura->getLocal() << endl;
		cout << "#" <<endl;
	}
}

void geraHistoricoIndividuoData(int id){
	list<capturas> lista = gerenCapturas->getListaCapturaPorIndividuo(id);

	list<capturas>::iterator itCaptura;
	
	capturas* maiorc;
	int maior = 0;
	for(itCaptura = lista.begin(); 
     		itCaptura != lista.end();
       		itCaptura++){
		
		capturas* capturad = &(*itCaptura);
		string d = capturad->getData();
		int dia;
		int ano;
		int mes;
		sscanf(d.c_str(),"%d/%d/%d",&dia,&mes,&ano);
		if(maior < dia+mes*10+ano*100){
			maior = dia+mes*10+ano*100;
			maiorc = capturad;		
		}
	}

	capturas* captura = maiorc;
	cout << "Encontrado." << endl;
	cout << "Id: " << id << endl;
	cout << "Id indivíduo: " << captura->getIdIndividuo() << endl;
	cout << "Comprimento: " << captura->getComprimento() << endl;
	cout << "Largura: " << captura->getLargura() << endl;
	cout << "Peso: " << captura->getPeso() << endl;
	cout << "Data: " << captura->getData() << endl;
	cout << "Local: " << captura->getLocal() << endl;
	cout << "#" <<endl;
	
}

void menuHistoricoEspecie(){
	int id;
	clear();
	cout << "Digite o id a espécie a ser buscada: ";
	scanf("%d",&id);
	list<int> listaE = gerenIndividuos->getListaDeIndividuosDeUmaEspecie(id);
	list<int>::iterator itIndividuo;
	clear();
	for(itIndividuo = listaE.begin(); 
     		itIndividuo != listaE.end();
       		itIndividuo++){	
	
		geraHistoricoIndividuo((*itIndividuo));
	}

	getchar();
	getchar();
}


void menuHistoricoIndividuo(){
	int id;
	clear();
	cout << "Digite o id do indivíduo a ser buscada: ";
	scanf("%d",&id);
	
	clear();
	geraHistoricoIndividuo(id);
	getchar();
	getchar();
}

void menuHistoricoIndividuoData(){
	int id;
	clear();
	cout << "Digite o id do indivíduo a ser buscada: ";
	scanf("%d",&id);
	
	clear();
	geraHistoricoIndividuoData(id);
	getchar();
	getchar();
}


void menuHistorico(){
	clear();
	cout << "Histórico:" << endl;
	cout << "	1 - Por indivíduo" << endl;
	cout << "	2 - Por espécie" << endl;
	cout << "	3 - Por indivíduo (Data)" << endl;
	cout << "	4 - Sair" << endl;
	cout << "escolha uma opção: ";
	int op;
	scanf("%d",&op);
	if(op == 1){
		menuHistoricoIndividuo();	
	}else if(op == 2){
		menuHistoricoEspecie();	
	}else if(op == 3){
		menuHistoricoIndividuoData();	
	}
	clear();
}

void load(fileIO* io){
	string line;
	int i = 0;
	bool next = true;
	while(next){
		line = io->readLine();
		next = !(strcmp(line.c_str(),"NULL") == 0);
		

		if(next == false){
			break;
		}

		if(strcmp(line.c_str(),"#") == 0){
			i++;	
		}else if(i==1){ //ESPECIES
			int id = atoi(line.c_str());
			string nomeCientifico = io->readLine();
			string nomePopular = io->readLine();
			string descricao = io->readLine();

			especies especie(id,nomeCientifico,nomePopular,descricao);
			if(gerenEspecies->busca(&especie) == -1){
				gerenEspecies->insere(especie);
			}else{
				cout << "Espécie já cadastrada" << endl; 
			}
		}else if(i==2){ //INDIVIDUOS
			int id = atoi(line.c_str());
			int idEspecie = atoi(io->readLine().c_str());
			char sexo = (io->readLine().c_str())[0];

			especies especie(idEspecie,string(""),string(""),string(""));
			if(gerenEspecies->busca(&especie) != -1){
				individuos individuo(idEspecie,id,sexo);
				if(gerenIndividuos->busca(&individuo) == -1){
					gerenIndividuos->insere(individuo);
				}else{
					cout << "ID do indivíduo já cadastrado." << endl;
					getchar();
				}
			}else{
				cout << "Espécie não existe!" << endl;
				getchar();
				getchar();
			}
	
		}else if(i==3){ //CAPTURAS
			int id = atoi(line.c_str());
	       		int idInd = atoi(io->readLine().c_str());
       			int c = atoi(io->readLine().c_str());
       			int l = atoi(io->readLine().c_str());
       			int p= atoi(io->readLine().c_str());
       			string d = io->readLine();
       			string local = io->readLine();

			capturas captura(id,idInd,c,l,p,d,local);
			if(gerenCapturas->busca(&captura) == -1){
				gerenCapturas->insere(captura);
			}else{
				cout << "Já existe esse ID" << endl;	
				getchar();
				getchar();	
			}
		}
	}
}

void menuCarregaArquivo(){
	clear();
	cout << "Digite Local/Nome do arquivo: ";
	string nomeArquivo;
	getchar();
	getline(cin, nomeArquivo, '\n');
	fileIO *io = new fileIO();
	if(!io->openFile(nomeArquivo)){
		cout << "Arquivo não encontrado" << endl;
		getchar();
		return;
	}else{ // File open
		load(io);
		io->closeFile();	
	}
	clear();
}

void menu(){
	int i=100;
	while(i!=0){
		i--;
		clear();
		cout << "Bem vindo. Escolha uma das opções: " << endl;
		cout << "	1 - gerenciar indivíduo" << endl;
		cout << "	2 - gerenciar espécies" << endl;
		cout << "	3 - gerenciar capturas" << endl;
		cout << "	4 - Gerar histórico" << endl;
		cout << "	5 - Carregar arquivo" << endl;
		cout << " 	6-  Imprimir árvore B" << endl;
		cout << "	7 - sair"<< endl;
		cout << "escolha uma opção: ";
		int op;
		scanf("%d",&op);
		if(op == 1){
			menuIndividuos();
		}else if(op == 2){
			menuEspecies();
		}else if(op == 3){
			menuCapturas();
		}else if(op == 4){
			menuHistorico();
		}else if(op==5){
			menuCarregaArquivo();
		}else if(op==6){
			clear();
			gerenEspecies->printTree(string("./arvoreBRaw"));	
			clear();
			printf("Árvore B gerada em arvoreBRaw;");
			getchar();
			getchar();
			clear();
		}else if(op >= 7){
			break;
		}
		clear();
	}	
}


void initIndividuos(){
	ioHeadIndividuos = new fileIO();
	ioHeadIndividuos->openFile(string("./data/headIndividuos"));
	pedIndividuos = new pilhaRegistros();
	pedIndividuos->loadHead(ioHeadIndividuos);
	gerenIndividuos = new gerenciadorIndividuos(pedIndividuos);
	gerenIndividuos->openFile(string("./data/individuos"));
}

void initEspecies(){
	ioHeadEspecies = new fileIO();
	ledEspecies = new listaDeRegistrosWorstFit();
	ioHeadEspecies->openFile(string("./data/headEspecies"));
	ledEspecies->loadHead(ioHeadEspecies);
	gerenEspecies = new gerenciadorEspecies(ledEspecies);
	gerenEspecies->openFile(string("./data/especies"));
}

void initCapturas(){
	ioHeadCapturas = new fileIO();
	ledCapturas = new listaDeRegistrosWorstFit();
	ioHeadCapturas->openFile(string("./data/headCapturas"));
	ledCapturas->loadHead(ioHeadCapturas);
	gerenCapturas = new gerenciadorCapturas(ledCapturas);
	gerenCapturas->openFile(string("./data/capturas"));
}

void close(){
	pedIndividuos->commitHead(ioHeadIndividuos);
	gerenIndividuos->close();
	ioHeadIndividuos->closeFile();

	ledEspecies->commitHead(ioHeadEspecies);
	ioHeadEspecies->closeFile();
	gerenEspecies->close();

	ledCapturas->commitHead(ioHeadCapturas);
	ioHeadCapturas->closeFile();
	gerenCapturas->close();
}


int main(void){
	initIndividuos();
	initEspecies();
	initCapturas();
	
	menu();
                                                                   
	close();
	return 0;
}
