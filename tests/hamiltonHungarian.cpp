// Problema da lista, passou. 
#include <bits/stdc++.h>
#include "../graphs/hungarian.cpp"
using namespace std;

int main(){
	int n; cin>>n;
	vector<vector<int>> m(n+1, vector<int>(n+1));
	for(int i = 1; i<=n; i++){
		for(int j = 1; j<=n; j++){
			cin>>m[i][j];
		}
	}

	// Vou ter uma matriz n x n, onde uma das dimensões será os (n+1)/2 vértices impares, 1, 3, 5 etc
	// e a outra será as (n+1)/2 posições em que se poderá colocar o vértice. O valor da matriz[i][j] será o
	// custo de utilizar o vértice i como ponte entre os vértices j*2 e j*2 + 1.
	vector<vector<int>> hungaro(1 + (n+1)/2, vector<int>(1 + (n+1)/2));
	for(int i = 1; i<=(n+1)/2; i++){
		int vi = 2*i - 1; // impar
		for(int j = 1; j<=(n+1)/2; j++){
			int vj1 = j*2 - 2, vj2 = j*2;
			// par anterior e par posterior
			int sum = (j > 1 ? m[vi][vj1] : 0) + (vj2 <= n ? m[vi][vj2] : 0);
			hungaro[i][j] = sum;
		}
	}
	cout<<hungarian(hungaro)<<endl;
}