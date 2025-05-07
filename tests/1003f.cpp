#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define INF INT_MAX

using namespace std;

void fast_io(){
	cin.tie(0);
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
	int vt_root;
	bool cmp(int u, int v){
		return st[u] < st[v];
	}
	Virtual_tree(int n, vector<int> &vert){
		adj_vt.assign(n, vector<int>());
		// Pick the needed vertices 
		sort(vert.begin(), vert.end(), cmp);
		int k = vert.size();
		for(int i = 0; i < k-1; i++){
			vert.push_back(lca(vert[i], vert[i+1]));
		}
		sort(vert.begin(), vert.end(), cmp);
		vert.erase(unique(vert.begin(), vert.end()), vert.end()); // Erase duplicates

		// build the actually virtual tree
		vector<int> st; st.push_back(vert[0]);

		for(int i = 1; i<vert.size(); i++){
			int u = vert[i];
			while(st.size() >= 2 && !is_ancestor(st.back(), u)){
				// add edge to the tree
				adj_vt[st[st.size()-2]].push_back(st.back()); 
				// here only the top -> bottom is added, which is fine as we only need to transverse it from the root to the leaves.
				st.pop_back();
			}
			st.push_back(u);
		}

		while(st.size() >= 2){
			adj_vt[st[st.size()-2]].push_back(st.back());
			st.pop_back();
		}
		vt_root = st[0];
	}

	bool solve(){

	}
};


void work(){
	cin>>n;
	adj.assign(n, vector<int>());
	values.resize(n);
	positions.assign(n, vector<int>());
	for(int i = 0; i < n; i++){
		cin>>values[i];
		positions[values[i]-1].push_back(i);
	}
	for(int i = 0; i < n-1; i++){
		int u, v; cin>>u>>v; u--; v--;
		adj[v].push_back(u);
	}
	int root;
	for(int i = 0; i<n; i++) if(adj[i].size() == 1) root = i;
	// just to make sure that I sent the correct root

	pre_compute_lca(root);
	
	for(int i = 0; i<n; i++){
		bool res = false;
		if(positions[i].size() > 1){
			Virtual_tree * vt = new Virtual_tree(n, positions[i]);
			res = vt->solve();
		}
		cout<<res;
	} cout<<endl;
	
}


int main(){
	int tt; cin>>tt;
	while(tt--) work();
}