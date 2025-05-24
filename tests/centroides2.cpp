// Xenia and tree
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Centroid{
	vector<int> subtree_size;
	vector<bool> is_removed;
	vector<vector<int>> adj;
	vector<vector<pair<int, int>>> ancestroids;
	vector<int> min_dist;
	Centroid(int v, vector<vector<int>> &g){
		subtree_size.assign(v, 0);
		is_removed.assign(v, false);
		ancestroids.assign(v, vector<pair<int, int>>());
		min_dist.assign(v, INT_MAX);
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
			min_dist[v] = min(min_dist[v], w);	
		}
		min_dist[u] = 0;
	}

	ll query(int u){
		ll menor = min_dist[u];
		for(auto e: ancestroids[u]){
			int v = e.first; ll w = e.second;
			menor = min(menor, w+(ll)min_dist[v]);
		}
		return menor;
	}
};




int main(){
	int t, q; cin>>t>>q;
	vector<vector<int>> v(t);
	for(int i = 0; i<t-1; i++){
		int u, w; cin>>u>>w;
		u--; w--;
		v[u].push_back(w);
		v[w].push_back(u);
	}
	Centroid *c = new Centroid(t, v);
	c->update(0);
	for(int i = 0; i<q; i++){
		int a, b; cin>>a>>b;
		b--;
		if(a == 1){
			c->update(b);
		} else {
			cout<<c->query(b)<<endl;
		}
	}
	
}