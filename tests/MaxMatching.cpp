#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define all(v) v.begin(), v.end()

vector<int> dist;
// BUILD A (Smaller Partition) AND B (Bigger partition)
vector<int> A, B;
vector<vector<int>> adj;
bool swapped = false;
int n;

int L, R, M;

bool increase(vector<int> &m, int u){
	for(auto v: adj[u]){
		if(m[v] == v || (dist[m[v]] == dist[u]+1 && increase(m, m[v]))){
			m[v] = u;
			m[u] = v;
			return true;
		}
	}
	return false;
}

bool augmenting_path(vector<int> &m){
	queue<int> q;
	for(int u: A) {
		if(m[u] == u){ // Separo todos os vértices sem matching para fazer a busca
			dist[u] = 0;
			q.push(u);
		} else dist[u] = INF;
	}
	
	int k = INF;
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(dist[u] < k) { // Só realizo a busca se dist[u] < Menor distância atual
			for(auto v: adj[u]){
				if(v == m[v] && k == INF) k = dist[u]+1; // não tem emparelhamento 
				else if(dist[m[v]] == INF){
					dist[m[v]] = dist[u]+1;
					q.push(m[v]);
				}
			}
		}
	}
	return k != INF;
}

void hopcroft_karp(){
	dist.resize(n);
	vector<int> m(n); // Emparelhamento, m[i] = i se i não está emparelhado, se não m[i] = v
	iota(m.begin(), m.end(), 0);
	
	int max_matching = 0;
	while(augmenting_path(m)){ // Caso ache um caminho aumentante
		for(int v: A){
			// Caso m[v] não tenha matching e seja possível aumentá-lo, irei fazê-lo e aumentar o contador.
			if(m[v] == v && increase(m, v)) max_matching++;
		}
	}


	cout<<max_matching<<endl;
	// bool dot = false;
	for(int v: A){
		if(m[v] != v) {
			// if(dot) cout<<", ";
			// dot = true;
			int x = v, y = m[v]-L;
			if(swapped){
				swap(x, y);
			}
			cout<<x<<" "<<y<<endl;
		}
	} 
}


int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>L>>R>>M;
	swapped = false;
	if(R < L) swap(R, L), swapped = true;
	A.resize(L);
	B.resize(R);
	iota(all(A), 0);
	iota(all(B), L);
	n = L+R;
	
	
	adj.assign(n, vector<int>());
	for(int i = 0; i<M; i++){
		int a, b; cin>>a>>b;
		if(swapped) swap(a, b);
		b+=L;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	hopcroft_karp();
}