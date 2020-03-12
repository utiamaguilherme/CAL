#include <bits/stdc++.h>
#define TAM 2

using namespace std;

vector<int> vet(TAM*TAM);
int aux[TAM][TAM], def[TAM][TAM], mat[TAM][TAM];
// int dx[] = {1,-1,0,0}, dy[] = {0,0,1,-1};
int ans;

bool ingraph(int i, int j){
    if(i >= 0 and i < TAM and j >= 0 and j < TAM)
        return true;
    return false;
}

void copia(){
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            mat[i][j] = aux[i][j];
        }
    }
}

void swap(int l, int c, int i, int j){
    int k = mat[i][j];
    mat[i][j] = mat[l][c];
    mat[l][c] = k;
}

void backtracking(){
    int cont = 0;
    ans++;
    for(int i=0, k=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            // cout << mat[i][j] << " ";
            if(mat[i][j] == def[i][j])   cont++;
            else    break;
        }
        // cout << endl;
    }
    cout << "ans: "<< ans <<endl;
    
    if(cont == TAM*TAM){
        cout << "Deu certo: " << ans << endl;
        return;
    } 
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            if(mat[i][j] == 0){
                if(ingraph(i-1,j)){
                    copia();
                    swap(i-1,j, i, j);
                    backtracking();
                }
                else break;
                if(ingraph(i+1,j)){
                    copia();
                    swap(i+1, j, i, j);
                    backtracking();
                }
                else break;
                if(ingraph(i,j-1)){
                    copia();
                    swap(i, j-1, i, j);
                    backtracking();
                }
                else break;
                if(ingraph(i,j+1)){
                    copia();
                    swap(i, j+1, i, j);
                    backtracking();
                }
                else break;
            }
        }
    }
}

void normal(){
    for(int i=0,k=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            def[i][j] = vet[k++];
        }
    }
}

int main(){
    //leitura
    int mat[TAM][TAM];
    for(int i=0, k=0; i<TAM; i++)
        for(int j=0; j<TAM; j++){
            cin >> mat[i][j];
            vet[k++] = mat[i][j];
            def[i][j] = mat[i][j];
            aux[i][j] = mat[i][j];
        }

    sort(vet.rbegin(), vet.rend());
    sort(vet.begin(), vet.end()-1);
    normal();
    backtracking();
    // for(auto i : vet)   cout << i << endl;
    cout << "Matriz original:\n\n";
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            cout << aux[i][j] << " ";
        }cout << endl;
    }

    cout << "Matriz normalizado:\n\n";
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            cout << mat[i][j] << " ";
        }cout << endl;
    }
}