#include <bits/stdc++.h>

using namespace std;

int main(){
    string name;
    getline(cin, name);
    map<char, int> mapinha;
    vector<pair<int, char>> letras;

    for(char c : name){
        mapinha[c]++;
    }

    for(auto c : mapinha){
        letras.push_back({c.second, c.first});
    }
    sort(letras.begin(), letras.end(), greater<pair<int,char>>());

    for(auto l : letras){
        cout << l.first << " " << l.second << endl;
    }
}
