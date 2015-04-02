#include <stdio.h>
#include <cstdlib>

void mult_mat(int *a, int *b, int *c, int n);

int main(){
	int n = 750;
	int* a = (int*) malloc(sizeof(int) * n*n);
	int* b = (int*) malloc(sizeof(int) * n*n);
	int* c = (int*) malloc(sizeof(int) * n*n);

	for(int i = 0; i < n*n; i++) {
		a[i] = i;
		b[i] = i/2;
	}

	mult_mat(a, b, c, n);
	return 0;
}

void mult_mat(int *a, int *b, int *c, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			c[i+n*j] = 0;
			for(int k=0;k<n;k++){
				c[i+n*j] += a[k+n*j] * b[i+n*k];
			}					
		}
	}
};
