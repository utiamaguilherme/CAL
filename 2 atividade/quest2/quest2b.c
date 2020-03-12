#include <stdio.h>
#define dim 100

int l,c,i,j,k;

void leitura(int mat[][dim]){
	for(i=0; i<l; i++){ //leitura da matriz
		for(j=0; j<c; j++){
			scanf("%d", &mat[i][j]);
		}
	}
}

void opera(int mat1[][dim], int mat2[][dim], int mat3[][dim]){
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			int ans = 0;
			for(k = 0; k<l; k++){
				ans+=(mat1[i][k]*mat2[k][j]);
			}
			mat3[i][j] = ans;
		}
	}
}

void show(int mat[][dim]){
	printf("\nMatriz resultante:\n");
	for(i=0; i<l; i++){
		for(j=0; j<c; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int main(void){

	printf("Insira a quantidade de linhas e colunas com espaçamento entre as quantidades de cada unidade:\n");
	scanf("%d %d", &l, &c);
	int mat1[l][c], mat2[l][c], mat3[l][c];
	printf("Leitura da primeira matriz:\n");
	leitura(mat1);
	printf("\n");
	printf("Leitura da segunda matriz:\n");
	leitura(mat2);
	opera(mat1, mat2, mat3);
	show(mat3);
	return 0;
}