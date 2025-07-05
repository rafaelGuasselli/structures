// Dado um problema onde a conexão entre dois vértices representa algo,
// é possível criar uma árvore dessas conexões e utilizá-la para fazer as operações 
// necessárias. Essa árvore terá como folhas os vértices originais, e até M nós
// extras, onde M é o número de arrestas, e cada nó representa a conexão de uma 
// sub-árvore com outra.

// Ex: Latin-America 2025, problem D
// cada vértice possui um peso, e o peso de um caminho é igual ao vértice de maior
// peso neste caminho. Objetivo: Qual a soma do peso do caminho de um vértice para todos os outros.
// Cada arresta é adicionada como um nó na DSU_tree, e seu peso é igual ao maior peso
// das sub-árvores que esta arresta conecta.

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> dsu_tree(600005);
vector<int> adj[600005];

vector<pair<int, int>> edges;

int getRoot(int u){
	if(u == dsu_tree[u]) return u;
	return dsu_tree[u] = getRoot(dsu_tree[u]);
}

void addEdge(int u, int v){
	u = getRoot(u), v = getRoot(v);
	
	dsu_tree[n] = dsu_tree[u] = dsu_tree[v] = n;

	adj[n].push_back(u);
	if(u != v) adj[n].push_back(v);

	++n;
}

void build(){
	for(int i = 0; i<n; ++i) dsu_tree[i] = i;
	
	for(int i = 0; i<m; ++i) {
		auto [u, v] = edges[i];
		addEdge(u, v);
	}
}