#include "../presets/base.cpp"

// Isso aqui é bem tranquilo na real. Você modela os estados e a probabilidade de ir de um estado para o outro como uma matriz de adjecências
// depois, para descobrir a matriz depois de M passos basta elevar essa matriz a M.
// Por fim, para descobrir a distribuição a partir de um estado inicial, basta multiplicar essa matriz^M por um vetor que representa o estado inicial
// (se o estado inicial for só o 1, por exemplo, e o tamanho da matriz for 5, você terá algo do tipo {{1}, {0}, {0}, {0}, {0}}.

vector<vector<ld>> mult(vector<vector<ld>> &A, vector<vector<ld>> &B){
	int n_r = A.size(), n_c = A[0].size();
	int m_r = B.size(), m_c = B[0].size(); // vou assumir que não terá nada de errado na passagem

	// if(n_c != m_r) cerr<<"IMPOSSIBLE\n";

	vector<vector<ld>> C(n_r, vector<ld>(m_c));

	for(int Ai = 0; Ai<n_r; Ai++){
		for(int Bj = 0; Bj < m_c; Bj++){
			ld k = 0;
			for(int i = 0; i < n_c; i++){
				k += A[Ai][i] * B[i][Bj];
			}
			C[Ai][Bj] = k;
		}
	}
	return C;
}

vector<vector<ld>> fast_pow(vector<vector<ld>> A, int n){
	int An = A.size(), Am = A[0].size(); // A deverá ter a mesma dimensão de linha e coluna, porém just in case
	vector<vector<ld>> res(An, vector<ld>(Am, 0));
	for(int i = 0; i<min(An, Am); i++) res[i][i] = 1;

	while(n){
		if(n & 1) res = mult(res, A);
		A = mult(A, A);
		n >>= 1;
	}
	return res;
}


vector<vector<ld>> markov_chain(vector<vector<ld>> states, int initial_state, int m){
	// markov chain after m steps
	vector<vector<ld>> initial_vector(states[0].size(), vector<ld>(1, 0));
	initial_vector[initial_state][0] = 1;

	vector<vector<ld>> states_pot = fast_pow(states, m);
	return mult(states_pot, initial_vector);
}

