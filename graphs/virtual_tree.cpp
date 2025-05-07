#include "lca.cpp"
// Solve problems like the query of a sum of the distance between all pair of given vertices in a tree
// It basically compress the tree to be just the important nodes (The considered vertices and their common ancestors),
// which are at most 2k-1, where k is the number of vertices considered (In k log k time). 
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
};
