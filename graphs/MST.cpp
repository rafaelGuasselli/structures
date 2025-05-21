#include "../presets/base.cpp"

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
 
bool cmp(pair<pair<int, int>, int> &a, pair<pair<int, int>, int> &b){
	return a.second < b.second;
}

int MST(int n, vector<pair<int, int>, int> &edges, vector<pair<pair<int, int>, int>> &tree){
	int m = edges.size();
	sort(edges.begin(), edges.end(), cmp);
	DSU dsu(n);

	int count = 1;
	double sum = 0;
	for(int e = 0; e<m && count < n; e++){
		int u = edges[e].first.first, v = edges[e].first.second;
		double w = edges[e].second;
		if(dsu.find(u) != dsu.find(v)){
			dsu.join(u, v);
			tree.push_back({{u, v}, w});
			count++;
			sum += w;
		}
	}
	return sum;
}
