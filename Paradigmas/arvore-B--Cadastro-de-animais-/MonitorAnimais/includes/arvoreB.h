#ifndef ARVOREB_H
#define ARVOREB_H
#include <stdlib.h>

 
class BTPage{
public:
	int D=5;
        //armazena numero de chaves na pagina
        short int totalChaves = 0;
 
        //vetor de chaves
        int* chaves;
	int* offset;
 
        //endereços das paginas filhas, -1 aponta para NULL
        int* filha; 

	BTPage(){
	        chaves = (int*) malloc((D-1)*sizeof(int));
                offset = (int*) malloc((D-1)*sizeof(int));
                filha = (int*) malloc(D*sizeof(int));
		int i;
		for(i=0;i<D;i++){
			filha[i] = -1;
		}
		for(i=0;i<D-1;i++){
			chaves[i]=-1;
			offset[i]=-1;
		}
	};
	BTPage(int d){
		chaves = (int*) malloc((d-1)*sizeof(int));
		offset = (int*) malloc((d-1)*sizeof(int));
		filha = (int*) malloc(d*sizeof(int));
		D=d;
                int i;
                for(i=0;i<D;i++){
                        filha[i] = -1;
                }
		 for(i=0;i<D-1;i++){
                        chaves[i]=-1;
                        offset[i]=-1;
                }

	};

	void setTotalChaves(int total){totalChaves = total;};  
	void setChave(int l,int value,int off){ 
						chaves[l] = value;
						offset[l] = off; 
						};
	int addChave(int chave,int off){
			bool swap = false;
			int i=0;
	                for(i=0;i<totalChaves;i++){
               	        	if(chaves[i]==chave){
               	                	return -1;
               	        	}else if(chaves[i] > chave){
					swap = true;
					break;	
               	        	}
	                }
			if(swap){
				int j;
				int aux,aux1 = chave;
				int aux2,aux3 = off;
				for(j=i;j<totalChaves+1;j++){
					aux=chaves[j];
					chaves[j]=aux1;
					aux1= aux;					

					aux2=offset[j];
					offset[j]=aux3;
					aux3=aux2;
				}	
			}else{
				setChave(i,chave,off);
			}
			setTotalChaves(getTotalChaves()+1);
			return i;

		};
	void removeChave(int chave){
		bool swap = false;
		int j,i=0;
                for(i=0;i<totalChaves;i++){
                        if(chaves[i]==chave){
                                break;
                        }
                }
		if(i<totalChaves-1){
			for(j=i;j<D-2;j++){	
				chaves[j] = chaves[j+1];
				offset[j] = offset[j+1];
			}
			for(j=i;j<D;j++){
				filha[j] = filha[j+1];
			}
		}
		setTotalChaves(getTotalChaves()-1);
					
	}
	void addFilha(int chave, int pos){
			int j,aux,aux1 = chave;	
			for(j=pos;j<D;j++){
				aux = filha[j];
				filha[j]=aux1;
				aux1=aux;
			}
		};
	void setFila(int l,int value){ filha[l] = value; };

	int getTotalChaves(){return totalChaves;};
	int getChave(int l){ return chaves[l]; };
	int getOff(int l){ return offset[l]; };
	int getFilha(int l){ return offset[l]; };
};	

#endif
