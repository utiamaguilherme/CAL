/*
 * Elabore um algoritmo recursivo para “gerar as posições de
 * marcação de uma régua” com comprimento informado por
 * parâmetro (posição esq/dir). A função recursiva receberá a altura
 * inicial efetuando a marcação central com esta altura. Divida a
 * régua em 4 partes e efetue uma nova marcação central com altura –
 * 1 em cada parte. E assim sucessivamente... Faça enquanto altura da
 * marca é maior que zero. Imprima na tela a posição da marca e sua
 * respectiva altura para testar. Após implementar o algoritmo,
 * escreva a relação de recorrência e a respectiva complexidade do
 * algoritmo para o pior caso.
 */


/*
*Alunos: Guilherme Utiama, Peter Brendel
*/


 /*
  * T(N) = 4T(N-1) + O(1)
  * 4T(N) = 4²T(N-2) + 4¹O(1)
  * 4²T(N) = 4³T(N-3) + 4²O(1)
  * ...
  * T(0) = O(1) ou 4^n O(1)
  * Somatorio i = 0 até n de 4^i
  * sum 4^j, j=0 to n (WolframAlpha)
  *
  */


#include <bits/stdc++.h>

using namespace std;

set<pair<double, int>> regua;

void dividirEconquistar(int altura, double esq, double dir){

    if(altura <= 0)
        return;
    double mid = (esq+dir)/2.0;
    if(mid > 15)    return;
    double size = dir - esq;
    double tam = size/4;
    double x1 = esq+tam;
    double x2 = dir-tam;

    regua.insert({mid, altura});
    if(altura-1 > 0){
        regua.insert({x1, altura-1});
        regua.insert({x2, altura-1});
    }

            dividirEconquistar(altura-1, esq, x1);
            dividirEconquistar(altura-1, x1, mid);
            dividirEconquistar(altura-1, mid, x2);
            dividirEconquistar(altura-1, x2, dir);
}

bool ver(pair<double,int> & vet, pair<double,int> & vet2){
    return vet.first < vet2.first;
}


int main(){

    double esq, dir;
    cin >> esq >> dir;
    double altura;
    cin >> altura;
    dividirEconquistar(altura, esq, dir);
    // sort(regua.begin(), regua.end(), ver);
    for(auto k : regua){
        cout << k.first << "\t";
        for(int i=0; i<k.second; i++){
            cout << '-';
        }
        cout << endl;

    }


}
