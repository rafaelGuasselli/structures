#include "../presets/base.cpp"

vector<vector<int>> c;
vector<vector<int>> adj;
int n;

int bfs(int s, int t, vector<int> &p){
	fill(all(p), -1);
	p[s] = -2;
	
	queue<pair<int, int>> q;
	q.push({s, INF});


	while(!q.empty()){
		int v = q.front().first, w = q.front().second;
		q.pop();

		for(int u: adj[v]){
			if(p[u] == -1 && c[v][u]){
				p[u] = v;
				int new_flow = min(w, c[v][u]);
				if(u == t) return new_flow;
				q.push({u, new_flow});
			}
		}
	}
	return 0;
}

int maxFlow(int s, int t){
	int flow = 0;
	vector<int> p(n);

	int new_flow;

	while(new_flow = bfs(s, t, p)){
		flow += new_flow;
		int cur = t;
		while(cur != s){
			int prev = p[cur];
			c[prev][cur] -= new_flow;
			c[cur][prev] += new_flow;
			cur = prev;
		}
	}
	
	return flow;
}