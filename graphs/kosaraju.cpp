#include "../base.cpp"

void dfs(int u, vector<bool> &v, vector<vector<int>> &adj, vector<int> &out){
	v[u] = true;
	for(int e: adj[u]){
		if(!v[e]) dfs(e, v, adj, out);
	}
	out.push_back(u);
}

void SCC(vector<vector<int>> &adj, vector<vector<int>> &componentes){
	int n = adj.size();
	vector<vector<int>> adj_T(n, vector<int>());
	for(int i = 0; i<n; i++){
		for(int u: adj[i]){
			adj_T[u].push_back(i);
		}
	}
	vector<bool> visitados(n, false);
	vector<int> st;
	for(int i = 0; i<n; i++){
		if(visitados[i]) continue;
		dfs(i, visitados, adj_T, st);
	}
	visitados.assign(n, false);
	reverse(st.begin(), st.end());

	for(auto v: st){
		if(!visitados[v]){
			vector<int> component;
			dfs(v, visitados, adj, component);
			componentes.push_back(component);
		}
	}
}