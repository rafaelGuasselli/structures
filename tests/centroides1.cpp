// Journey of Robber - Latino americana 2023-2024
// Para cada vértice, quer-se verificar qual o vértice mais próximo de índice maior que o atual
// Para isso, usamos centróides. 

#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Centroid{
	vector<int> subtree_size;
	vector<bool> is_removed;
	vector<vector<int>> adj;
	vector<vector<pair<int, int>>> ancestroids;
	vector<pair<int, int>> min_dist;
	Centroid(int v, vector<vector<int>> &g){
		subtree_size.assign(v, 0);
		is_removed.assign(v, false);
		ancestroids.assign(v, vector<pair<int, int>>());
		min_dist.assign(v, {});
		for(int i = 0; i<v; i++){
			min_dist[i] = {INT_MAX, i};
		}
		adj = g;
		build(0);
	}

	int get_subtree_size(int u, int parent = -1){
		subtree_size[u] = 1;
		for(int v: adj[u]){
			if(v == parent || is_removed[v]) continue;
			subtree_size[u] += get_subtree_size(v, u);
		}
		return subtree_size[u];
	}

	int get_centroid(int u, int tree_size, int parent = -1){
		for(int v: adj[u]){
			if(v == parent || is_removed[v]) continue;
			if(subtree_size[v] * 2 > tree_size){
				return get_centroid(v, tree_size, u);
			}
		}
		return u;
	}

	void build(int u){
		int subtree_size = get_subtree_size(u);
		int centroid = get_centroid(u, subtree_size);

		for(int v: adj[centroid]){
			if(!is_removed[v]){
				set_dists(v, centroid, centroid, 1);
			}
		}
		is_removed[centroid] = true;
		
		for(int v: adj[centroid]){
			if(!is_removed[v]){
				build(v);
			}
		}
	}

	void set_dists(int v, int centroid, int parent, int dist){
		ancestroids[v].push_back({centroid, dist});
		for(int w: adj[v]){
			if (w == parent || is_removed[w]) continue;
			set_dists(w, centroid, v, dist+1);
		}
	}

	void update(int u){
		for(auto e: ancestroids[u]){
			int v = e.first, w = e.second;
			min_dist[v] = min(min_dist[v], {w, u});	
		}
		min_dist[u] = {0, u};
	}

	ll query(int u){
		ll menor = min_dist[u].first;
		int menor_v = min_dist[u].second;
		for(auto e: ancestroids[u]){
			int v = e.first; ll w = e.second;

			if(menor > w+(ll)min_dist[v].first){
				menor = w+(ll)min_dist[v].first;
				menor_v = min_dist[v].second;
			} else if (menor == w+(ll)min_dist[v].first){
				if(min_dist[v].second < menor_v){
					menor = w+(ll)min_dist[v].first;
					menor_v = min_dist[v].second;
				}
			}
		}
		return menor_v;
	}
};

int main(){
	int a; cin>>a;
	vector<vector<int>> v(a);
	for(int i = 0; i<a-1; i++){
		int u, w; cin>>u>>w;
		u--; w--;
		v[u].push_back(w);
		v[w].push_back(u);
	}
	Centroid *c = new Centroid(a, v);
	/* Até aqui mesma coisa do centróide
	Irei dar update e query de trás para frente. Dessa forma, quando
	fizer a query de u, somente vértices maiores que u estarão nas
	distâncias mínimas. Caso não alcance nenhum vértice, retorna u.
	*/
	vector<int> caminhos(a);
	for(int i = a-1; i>=0; i--){
		caminhos[i] = c->query(i)+1;
		c->update(i);
	}
	for(int i = 0; i<a; i++){
		if(i) cout<<" ";
		cout<<caminhos[i];
	} cout<<endl;
	
}