// Também conhecida por eertree (acho que é um trocadilho)
#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26; // a-z

struct Node { // nó que armazena o palindromo
    int len; // tamanho do palindromo
    Node *prev; // Ponteiro ao maior palindromo contido neste (Ex: 'racecar' -> 'aceca' -> 'cec' etc)
    Node *next[ALPHABET_SIZE]; // ponteiro aos próximos palindromos (Ex: 'c' ->(e)-> 'ece')

    Node(int l = 0, Node *s = nullptr) : len(l), prev(s) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            next[i] = nullptr;
        }
    }
};

struct Eertree {
    string s; // string processada
    vector<Node*> tree;
    int num; // número de palindromos possiveis
    Node *suff; // Ponteiro ao maior sufixo atual que é palindromo (Ex: 'eertr' -> 'rtr')

    Eertree(string aux_s = "") {
		tree.emplace_back(new Node(-1)); // nó imaginário
		tree.emplace_back(new Node(0)); // nó vazio
		tree[0]->prev = tree[0]; // -1 aponta para ele mesmo
		tree[1]->prev = tree[0]; // 0 aponta ao -1

		num = 2;
		suff = tree[1];

		for(char e: aux_s) add(e);
    }

	 void add(char ch) {
        s += ch;
        int c = ch - 'a';
        Node *cur = suff; // pega o atual sufixo palindromo

		  int N = s.size();
		  // Retrocede no cur até encontrar um palindromo que possa ser expandido.
		  // ou seja, no caso de um 'e', retrocede até encontrar algo do tipo 'e' ou 'epqp'
        while (true) {
            if (N - cur->len - 2 >= 0 && s[N - cur->len - 2] == ch) {
                break;
            }
            cur = cur->prev;
        }

		  // O palindromo nesse caso já existia na árvore. Somente atualiza o maior sufixo
        if (cur->next[c] != 0) {
            suff = cur->next[c];
            return;
        }
		  
		  // cria o novo nó.
        tree.emplace_back(new Node(cur->len + 2));
		  suff = tree[num++];

        cur->next[c] = suff;

		  // Caso o caractere seja unico, seu predecessor deve ser a string vazia
        if (suff->len == 1) {
            suff->prev = tree[1];
            return;
        }

		  // note: o próximo do cur com o caractere c é o atual(suff), mas o anterior do atual não necessariamente é o cur. O anterior, na verdade, não é exatamente o anterior, mas achei confuso de outra forma. Ele é um palindromo anterior ao atual que também representa o sufixo do palindromo atual.

		  // por isso existe esse while no lugar de simplesmente suff->prev = cur.
        while (true) {
            cur = cur->prev;
            if (N - cur->len - 2 >= 0 && s[N - cur->len - 2] == ch) {
                suff->prev = cur->next[c];
                break;
            }
        }
    }
};

int main() {
    string text = "eertree";
    Eertree *et = new Eertree(text);

    // The number of unique palindromic substrings is the node count minus the two roots.
    std::cout << "The string \"" << text << "\" has " << et->num - 2 << " unique palindromic substrings." << std::endl;


    return 0;
}