#pragma optimize ("02")
#include <bits/stdc++.h>
// #define int long long
#define ll long long
#define all(v) v.begin(), v.end()
using namespace std;

vector<int> dsu_tree(600005);
ll peso[600005];
vector<int> adj[600005];
ll folhas[600005];

vector<pair<int, int>> edges, new_edges;

int n, m;

bool cmp(pair<int, int> &a, pair<int, int> &b){
	return max(peso[a.first], peso[a.second]) < max(peso[b.first], peso[b.second]);
}

struct DSU {
  vector<int> parent, size;
  DSU(int n) {
    parent.resize(n);
    size.resize(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      size[i] = 1;
    }
  }
 
  int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
  }
  void join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (size[a] < size[b]) swap(a, b);
    parent[b] = a;
    size[a] += size[b];
  }
};
 
void MST(){
  sort(edges.begin(), edges.end(), cmp);
  DSU dsu(n);

  for(int i = 0; i<m; i++){
	 auto [a, b] = edges[i];
	 if(dsu.find(a) != dsu.find(b)){
		dsu.join(a, b);
		new_edges.push_back(edges[i]);
	 }
  }
  m = new_edges.size();
}


int getRoot(int u){
	if(u == dsu_tree[u]) return u;
	return dsu_tree[u] = getRoot(dsu_tree[u]);
}

void addEdge(int u, int v){
	u = getRoot(u), v = getRoot(v);
	
	dsu_tree[n] = n;
	dsu_tree[u] = dsu_tree[v] = n;
	peso[n] = max(peso[u], peso[v]);

	adj[n].push_back(u);
	if(u != v) adj[n].push_back(v);

	++n;
}

void build(){
	for(int i = 0; i<n; ++i) dsu_tree[i] = i;
	
	for(int i = 0; i<m; ++i) {
		auto [u, v] = new_edges[i];
		addEdge(u, v);

	}
}

int N;
vector<ll> res;

void leafs(){
	stack<int> s1, s2;
	s1.push(n-1);
	while(!s1.empty()){
		int v = s1.top(); s1.pop();
		s2.push(v);
		for(int u : adj[v]) s1.push(u); 
	}
	while(!s2.empty()){
		int v = s2.top(); s2.pop();
		if(adj[v].empty()) folhas[v] = 1;
		else{
			folhas[v] = 0;
			for(int u: adj[v]) folhas[v] += folhas[u];
		}
	}
}

void build_answer(){
	stack<tuple<int, ll, int, ll>> s;
	s.push({n-1, 0LL, -1, 0LL});
	
	while(!s.empty()){
		auto [v, w, p, pw] = s.top(); s.pop();
		
		if(v < N) {
			if(peso[v] != peso[p]) {
				pw = pw - peso[p] + peso[v];
			}
			res[v] = pw; 
			continue;
		}	
		
		ll k = peso[v]*folhas[v];
		if(p != -1) k+=w;
		
		for(int i = adj[v].size()-1; i>=0; --i){
			int u = adj[v][i];
			if(u != p){
				ll nw = w+(folhas[v]-folhas[u])*peso[v];
				s.push({u, nw, v, k});
			}
		}
	}
}



signed main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	// cout.tie(nullptr);
	cin>>n>>m;
	N = n; res.resize(n);

	memset(folhas, 0LL, sizeof(folhas));
	memset(peso, 0LL, sizeof(peso));
	for(int i = 0; i<n; ++i){
		cin>>peso[i];
	}
	edges.resize(m);
	for(int i = 0; i<m; i++){
		int a, b; cin>>a>>b; a--, b--;
		edges[i] = make_pair(a, b);
	}

	MST(); // Deixa somente as melhores arestas
	build(); // Constroi a árvore da DSU
	leafs(); // Calcula a quantidade de folhas de cada vértice
	build_answer(); // Constrói o vetor resposta
	
	
	
	for(int i = 0; i<N; ++i){
		// if(i) cout<<" ";
		// cout<<res[i];
		if(i) printf(" ");
		printf("%lld", res[i]);
	}
	printf("\n");
	// cout<<endl;
	
}