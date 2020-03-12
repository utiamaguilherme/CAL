#include <bits/stdc++.h>

#define max 100000
using namespace std;

long long int vet[max];

void bubble(int n){
    int i, j, aux;
    for (i = n - 1; i > 0; i--){
        for (j = 0; j < i; j++){

            if (vet[j] > vet[j+1]){
                    aux = vet[j];
                    vet[j] = vet[j+1];
                    vet[j+1] = aux;
            }
        }
    }
}

void selectionSort(int n){
    int i, j, x, aux;
    for (i = 0; i < n; i++){
        x = i;
        for (j = i+1; j < n; j++){
            if( vet[j] < vet[x] )
                x = j;

        }
        aux = vet[i];
        vet[i] = vet[x];
        vet[x] = aux;
    }
}

void insercao(int n){
    int i, j, x;
    for (i = 1; i < n; i++){
        x = vet[i];
        j = i - 1;
        while (j >= 0 && vet[j] > x){
            vet[j+1] = vet[j];
            j--;
        }
        vet[j+1] = x;
    }
}

int main(void){
    clock_t begin = clock();
    memset(vet, -1, sizeof(vet));
    for(int i=0; i<max; i++)    cin >> vet[i];
    // bubble(max);
    selectionSort(max);
    // insercao(max);
    // for(int i=0; i<max; i++)    cout << vet[i] << endl;
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    return 0;
}
