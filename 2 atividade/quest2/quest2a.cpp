#include <bits/stdc++.h>

using namespace std;

int expo(int b, int e){
    return pow(b,e);
}

int main(void){
    clock_t begin = clock();
    int a, b;   cin >> a >> b;
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC;
    cout << expo(a,b) << endl;
    return 0;
}
