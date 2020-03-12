#include <bits/stdc++.h>

#define COUNT 4

using namespace std;

typedef struct node {
    pair<int,char> data;
    char bin;
    struct node * left;
    struct node * right;

    node(pair<int,char> c) {
        this->data = c;
        this->left = NULL;
        this->right = NULL;
    }

    bool operator<(struct node& other){
        return this->data.first < other.data.first;
    }
    bool operator>(struct node& other){
        return this->data.first > other.data.first;
    }

} Node;

struct node_cmp {
   bool operator()( const Node* a, const Node* b ) const {
    return a->data.first > b->data.first;
   }
};
void print_q(priority_queue<Node*, vector<Node*>, node_cmp> pq ){
    while(!pq.empty()){
        cout << pq.top()->data.first << " " << pq.top()->data.second << " -> ";
        pq.pop();
    }
}

class Tree {
public:
    Node * root;
    Tree();
    void generate(vector<pair<int, char>>& inputs);
    void show(Node * first, int space);
};

Tree::Tree(){
    // this->root = new Node();
}

void Tree::generate(vector<pair<int, char>>& inputs) {
    priority_queue< Node*, vector<Node*>, node_cmp > pq;
    for(auto c : inputs){
        pq.push(new Node(c));
    }
    // print_q(pq);
    // cout << "start\n";
    while(pq.size()-1){
        Node * right = pq.top(); pq.pop();
        right->bin = '0';
        Node * left = pq.top(); pq.pop();
        left->bin = '1';
        pair<int, char> tdata;
        tdata.first = left->data.first + right->data.first;
        tdata.second = '\0';
        Node * novo = new Node(tdata);
        novo->left = left;
        novo->right = right;
        pq.push(novo);
        // print_q(pq);
        // cout << "iterate\n";
    }

    this->root = pq.top();
    pq.pop();
}

void Tree::show(Node *now, int space) {
    if (now == NULL)
        return;
    space += COUNT;
    this->show(now->right, space);

    for (int i = COUNT; i < space; i++){
        cout << " ";
    }
    if(now->data.second != '\0')
        cout << now->data.second << ":";
    cout << now->data.first << endl;
    this->show(now->left, space);
}

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

    // for(auto l : letras){
    //     cout << l.first << " " << l.second << endl;
    // }

    Tree * tree = new Tree();
    tree->generate(letras);
    tree->show(tree->root, 0);
}
