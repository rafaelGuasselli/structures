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

	//1 - if has negative cycles; 0 - if not
	int bellmanFord(int s) {
		dist.clear();
		dist.assign(adj.size(), 1e9);
		
		dist[s] = 0;
		int cycle = 0;
		for (int k = 0; k <= adj.size(); k++) {
			for (int u = 0; u < adj.size(); u++) {
				for (pair<int, int> edge: adj[u]) {
					int v = edge.second;
					int w = edge.first;

					if (dist[u]+w<dist[v]) {
						dist[v] = dist[u]+w;
						if (k == adj.size()) {
							cycle = 1;
						}
					}
				}
			}
		}

		return cycle;
	}
};
 