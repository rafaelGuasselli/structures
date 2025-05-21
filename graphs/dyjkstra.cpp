#include "../presets/base.cpp"
struct Graph {
	vector<vector<pair<int, int>>> adj;
	vector<int> dist;

	void create(int numberOfVertices) {
		adj.clear();
		adj.assign(numberOfVertices, {});
	}

	void addEdge(int u, int v, int w){
		adj[u].push_back({w, v});
	}

	void dyjkstra(int s) {
		dist.clear();
		dist.assign(adj.size(), 1e9);
		
		priority_queue<pair<int, int>> q;
		q.push({0, s});

		while (!q.empty()) {
			int u = q.top().second;
			int cost = q.top().first; q.pop();

			if (cost == dist[u]) {
				for (pair<int, int> edge: adj[u]) {
					int v = edge.second;
					int w = edge.first;

					if (cost+w < dist[v]) {
						dist[v] = cost+w;
						q.push({dist[v], v});
					}
				}
			}
		}
	}
};
 