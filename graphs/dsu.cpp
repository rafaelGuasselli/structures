#include<bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> parent, size;
	void create(int n) {
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
 