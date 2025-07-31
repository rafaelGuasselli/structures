// preset for generating a random tree that can be used for debugging 
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
  return a + rand()%(b - a + 1);
}

int N, root;

int main(int argc, char *argv[]){
  srand(atoi(argv[1]));
	
	N = rand(1, 10); // num of vertices 
	// always N-1 edges.
	root = rand(1, N); // Aqui a raiz é aleatória, mas pode ser fixa em 1 se preciso
	cout<<N<<endl;

	vector<int> connected_vertices;
	set<int> check_v;
	check_v.insert(root);
	connected_vertices.push_back(root);

	for(int i = 1; i<=N; i++){
		if(check_v.count(i)) continue;
		// Se o vertice não estiver conectado a raiz, vou conectar ele a um vértice aleatório que está conectado na raiz.
		int j = rand(1, connected_vertices.size());
		cout<<i<<" "<<connected_vertices[j-1]<<endl;
		check_v.insert(i);
		connected_vertices.push_back(i);
	}
}
