#include "../base.cpp"

void dfs(int u, vector<bool> &v, vector<vector<int>> &adj, vector<int> &out){
	v[u] = true;
	for(int e: adj[u]){
		if(!v[e]) dfs(e, v, adj, out);
	}
	out.push_back(u);
}

void topological_sort(vector<vector<int>> &adj, vector<int> &st){
	int n = adj.size();
	vector<vector<int>> adj_aux(n);
	for(int i = 0; i<n; i++){
		for(int u: adj[i])
			adj_aux[u].push_back(i);
	}
	vector<bool> visitados(n, false);

	for(int i = 0; i<n; i++){
		if(!visitados[i]){
			dfs(i, visitados, adj_aux, st);
		}
	}
}
