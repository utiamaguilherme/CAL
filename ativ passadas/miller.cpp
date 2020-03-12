#include <bits/stdc++.h>
/*
    *Nome: Guilherme Utiama, Peter Brendel
    *Disciplina: Complexidade de algoritmos
    *TC-CAL09
    *Complexidade de tempo: O(n²)
    *Complexidade de espaço: O(n)
    *Quantidade de numeros corretos: 
    *
*/
using namespace std;

bool witness(long long a, long long n){
    a = a*a-1;
    return a%n;
}

bool miller(long long n, long long s){
    srand(time(NULL));
    for(long long i=1; i <= s; i++){
        long long a = rand() % 100;
        if(witness(a,n)){
            return false;
        }
    }
    return true;
}

int main(){
    long long n; cin >> n;
    long long crivo[n+5];
    memset(crivo, -1, sizeof(crivo));
    crivo[0] = 0;
    crivo[1] = 0;
    // long long mn = ceil(sqrt(n));
    long long mn = ceil(n / 2);

    for (long long i = 2; i <= n; i++) {
        if(crivo[i] == -1){
            crivo[i] = 1;
            for(long long j=i+i; j<=n; j+=i){
                crivo[j] = 0;
            }
        }
    } //nlog(n)

    for(long long j=1; j<=n; j++){
        cout << crivo[j] << " ";
        if(j % 10 == 0){
            cout << '\n';
        }
    }


    long long p=0, np=0;
    for(long long i=1000; i<=n; i++){

        if(p < 20 && crivo[i]){
            cout << "p " << p << ": ";
            if(!miller(i, 5)){
                cout << i << " Falso negativo ? (" << i <<  " eh primo)\n";
            }else{
                cout << i << " Eh primo mesmo\n";
            }
            p++;
        }

        if(np < 20 && !crivo[i]){
            cout << "np " << np << ": ";
            if(miller(i, 5)){
                cout << i << " Falso positivo (" << i << " nao eh primo)\n";
            }else{
                cout << i << " nao eh primo mesmo\n";
            }
            np++;
        }

        if(p==np && p==20)
            break;
    } //O(n²)

}
