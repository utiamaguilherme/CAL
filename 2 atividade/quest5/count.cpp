#include <bits/stdc++.h>

using namespace std;

int main() {

  int aux;
  int n; cin >> n;
  vector<int> vet(n);
  for(int i=0; i<n; i++){
    cin >> vet[i];
  }

  vector<int>::iterator it = max_element(vet.begin(), vet.end());
  vector<int> count(*it+1, 0);

  for(int i : vet)
    count[i]++;

  for(int i=0, pos=0, max = count.size(), last = vet.size(); i < max && pos < last; i++){
    for(int j=0; j < count[i]; j++){
      vet[pos++] = i;
    }
  }

  for(int i : vet){
    cout << i << " ";
  }
  cout << endl;

}
