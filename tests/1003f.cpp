#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define INF INT_MAX

using namespace std;

void fast_io(){
	cout.tie(0);
	ios_base::sync_with_stdio(0);
}

// LCA by binary_lifting

vector<int> st, en, depth, values; // depth is not needed for lca but for the virtual_tree
vector<vector<int>> adj, up, positions; // up is the "ancestors" vector but up[i][j] is the 2^j ancestor of i.
int n, tmp, max_it;
void dfs(int v, int p){
	st[v] = ++tmp;	
	up[v][0] = p;
	for(int i = 1; i<= max_it; i++){
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for(int e: adj[v]){
		if(e != p){
			depth[e] = depth[v]+1;
			dfs(e, v);
		}
	}
	en[v] = ++tmp;
}
bool is_ancestor(int u, int v){
	return st[u] <= st[v] && en[v] <= en[u]; // v is inside u
}

int lca(int u, int v){
	if(is_ancestor(u, v)) return u;
	if(is_ancestor(v, u)) return v;
	for(int i = max_it; i>=0; --i){
		if(!is_ancestor(up[u][i], v)) u = up[u][i];
	}
	return up[u][0];
}

void pre_compute_lca(int root){
	st.resize(n); en.resize(n); depth.resize(n);
	depth[root] = 0;
	tmp = 0;
	max_it = ceil(log2(n));
	up.assign(n, vector<int>(max_it+1));
	dfs(root, root);
}

struct Virtual_tree{
	vector<vector<int>> adj_vt;
	vector<bool> important;
	int vt_root;
	static bool cmp(int u, int v){
		return st[u] < st[v];
	}
	~Virtual_tree() {
		for (auto &edges : adj_vt) {
			edges.clear();
		}
		adj_vt.clear();
		important.clear();
	}
	Virtual_tree(){}
	Virtual_tree(int n, vector<int> &vert){
		adj_vt.assign(n, vector<int>());
		important.assign(n, false);
		for(int e: vert) important[e] = true;
		// Pick the needed vertices 
		sort(vert.begin(), vert.end(), cmp);
		int k = vert.size();
		for(int i = 0; i < k-1; i++){
			vert.push_back(lca(vert[i], vert[i+1]));
		}
		sort(vert.begin(), vert.end(), cmp);
		vert.erase(unique(vert.begin(), vert.end()), vert.end()); // Erase duplicates

		// build the actually virtual tree
		vector<int> st_v; st_v.push_back(vert[0]);

		for(int i = 1; i<vert.size(); i++){
			int u = vert[i];
			while(st_v.size() >= 2 && !is_ancestor(st_v.back(), u)){
				// add edge to the tree
				adj_vt[st_v[st_v.size()-2]].push_back(st_v.back()); 
				// here only the top -> bottom is added, which is fine as we only need to transverse it from the root to the leaves.
				st_v.pop_back();
			}
			st_v.push_back(u);
		}

		while(st_v.size() >= 2){
			adj_vt[st_v[st_v.size()-2]].push_back(st_v.back());
			st_v.pop_back();
		}
		vt_root = st_v[0];
	}

	void print_tree(int v){
		cout<<"Vertice: "<<v<<" "<<(important[v] ? "Importante" : "")<<endl;
		cout<<"Filhos:";
		for(int e: adj_vt[v]) cout<<" "<<e;
		cout<<endl;
		for(int e: adj_vt[v]) print_tree(e); 
	}

	int dist(int u, int v){
		return abs(depth[u] - depth[v]);
	}

	bool solve(int v, int last_important = -1){
		if(important[v]){
			if(last_important != -1){
				if(dist(v, last_important) <= 2) return true;
			}
			for(int e: adj_vt[v]){
				if(solve(e, v)) return true;
			}
		} else {
			int count_ = 0;
			for(int e: adj_vt[v]){
				if(important[e] && dist(v, e) == 1) count_++;
			}
			if(count_ >= 2) return true;
			for(int e: adj_vt[v]){
				if(solve(e, last_important)) return true;
			}
		}
		return false;
	}

	bool solve(){
		// Aqui já vou ter a árvore reduzida
		// Res vai ser verdadeiro se: A distância entre dois vértices importantes for menor igual à dois, isto é, há no máximo um vértice
		// entre eles. A distância de u até v é o abs(depth[u] - depth[v]), onde depth é o vetor profundidade gerado pela dfs no LCA.
		return solve(vt_root);
	}
};


void work(){
	cin>>n;
	adj.assign(n, vector<int>()); // outgoing edges
	values.resize(n);
	positions.assign(n, vector<int>());
	for(int i = 0; i < n; i++){
		cin>>values[i];
		positions[values[i]-1].push_back(i);
	}
	for(int i = 0; i < n-1; i++){
		int u, v; cin>>u>>v; u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int root = 0;
	// cout<<root<<endl;
	// just to make sure that I sent the correct root

	pre_compute_lca(root);
	string res_ = "";
	Virtual_tree vt;
	for(int i = 0; i<n; i++){
		bool res = false;
		if(positions[i].size() > 1){
			vt = Virtual_tree(n, positions[i]);
			// if(i == 11) vt->print_tree(vt->vt_root);
			res = vt.solve();
		}
		res_.push_back(res ? '1' : '0');
	} cout<<res_<<endl;	
}

int main(){
	fast_io();
	int tt; cin>>tt;
	while(tt--) work();
}