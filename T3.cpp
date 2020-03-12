#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class Node
{
    int *chaves;
    int t;
    Node **dados;
    int numKeys;
    bool folha;

public:
    Node(int _t, bool _leaf);
    void inserirNaoCheio(int k);
    void divideDados(int i, Node *y);
    void print();
    friend class Arvore;
};

class Arvore
{
    Node *root;
    int t;

public:
    Arvore(int _t)
    {
        root = NULL;
        t = _t;
    }

    void print()
    {
        if (root != NULL)
            root->print();
    }

    void inserir(int k);
};

Node::Node(int t1, bool leaf1)
{
    t = t1;
    folha = leaf1;

    chaves = new int[2 * t - 1];
    dados = new Node *[2 * t];

    numKeys = 0;
}

void Node::print()
{
    int i;
    for (i = 0; i < numKeys; i++)
    {
        if (folha == false)
            dados[i]->print();
        cout << " " << chaves[i];
    }

    if (folha == false)
        dados[i]->print();
}

void Arvore::inserir(int k)
{
    if (root == NULL) // Arvore vazia
    {
        root = new Node(t, true);
        root->chaves[0] = k;
        root->numKeys = 1;
    }
    else
    {
        // Se a raiz atingi o limite, a altura aumenta e eh feito um balanceamento entre os dados filhos
        if (root->numKeys == 2 * t - 1)
        {
            Node *s = new Node(t, false);
            s->dados[0] = root;
            s->divideDados(0, root);

            int i = 0;
            if (s->chaves[0] < k)
                i++;
            s->dados[i]->inserirNaoCheio(k);

            root = s;
        }
        else // Se a raiz nao esta cheia, ele insere o dado no vetor filho
            root->inserirNaoCheio(k);
    }
}

void Node::inserirNaoCheio(int k)
{
    int i = numKeys - 1;

    if (folha == true)
    {
        while (i >= 0 && chaves[i] > k)
        {
            chaves[i + 1] = chaves[i];
            i--;
        }

        chaves[i + 1] = k;
        numKeys = numKeys + 1;
    }
    else
    {
        while (i >= 0 && chaves[i] > k)
            i--;

        if (dados[i + 1]->numKeys == 2 * t - 1)
        {
            divideDados(i + 1, dados[i + 1]);
            if (chaves[i + 1] < k)
                i++;
        }
        dados[i + 1]->inserirNaoCheio(k);
    }
}

void Node::divideDados(int i, Node *y)
{
    Node *z = new Node(y->t, y->folha);
    z->numKeys = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->chaves[j] = y->chaves[j + t];

    if (y->folha == false)
    {
        for (int j = 0; j < t; j++)
            z->dados[j] = y->dados[j + t];
    }

    y->numKeys = t - 1;

    for (int j = numKeys; j >= i + 1; j--)
        dados[j + 1] = dados[j];

    dados[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--)
        chaves[j + 1] = chaves[j];

    chaves[i] = y->chaves[t - 1];

    numKeys = numKeys + 1;
}

int main()
{
    ifstream ip("ordenado.csv");

    if (!ip.is_open())
    {
        cout << "Erro ao abrir arquivo " << endl;
        exit(EXIT_FAILURE);
    }

    Arvore t(6);

    string nomePaciente, nomeMedico, codSeq, dataInternacao, codMotivoInternacao, listaSintomas, tamBytes, index;

    int option;
    bool skipHeader = false;
    cout << "Deseja inserir de acordo com qual campo?\n 1- Codigo Sequencial\n 2- Codigo Motivo da Internacao\n 3- Tamanho de Bytes\n 4- Index\n";
    cin >> option;
    if (option == 1 || option == 2 || option == 3 || option == 4)
    {
        while (ip.good())
        {
            getline(ip, nomePaciente, ',');
            getline(ip, nomeMedico, ',');
            getline(ip, codSeq, ',');
            getline(ip, dataInternacao, ',');
            getline(ip, codMotivoInternacao, ',');
            getline(ip, listaSintomas, ',');
            getline(ip, tamBytes, ',');
            getline(ip, index, '\n');

            if (!skipHeader)
            {
                skipHeader = true;
            }
            else
            {
                if (option == 1)
                    t.inserir(atoi(codSeq.c_str()));
                if (option == 2)
                    t.inserir(atoi(codMotivoInternacao.c_str()));
                if (option == 3)
                    t.inserir(atoi(tamBytes.c_str()));
                if (option == 4)
                    t.inserir(atoi(index.c_str()));
            }
        }
    }
    else
    {
        cout << "Opcao invalida" << endl;
    }

    ip.close();

    cout << "Print Index InOrder ";

    t.print();

    return 0;
}
