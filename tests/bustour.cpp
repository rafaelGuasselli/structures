#include "../presets/base.cpp"

// QUESTION KATTIS bustour - Bus Tour
// TESTING: DP -> tsp


int dp1[18][1000000], dp2[18][1000000];
int adj[30][30];
int n,m;

// ideia: fazer dois TSP um saindo de 0 e outro saindo de n
// depois comparar os caminhos ja visitados no meio do caminho
// encontra a menor soma saindo da esquerda e chegando num no v
// outro que comece em v e chegue no fim a mesma coisa para fim - inicio

int main() {
    int t = 0;
    while(cin>>n>>m) {
        memset(adj, 0x3f, sizeof(adj));
        for(int i=0;i<m;i++) {
            int a,b,c;cin>>a>>b>>c;
            adj[a][b] = adj[b][a] = c;
        }

        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if (i == j) continue;   
                for(int k =0;k<n;k++) {
                    adj[i][j] = adj[j][i] = min(adj[i][j], adj[i][k] + adj[k][j]); 
                }
            }
        }

        memset(dp1, 0x3f, sizeof(dp1));
        memset(dp2, 0x3f, sizeof(dp2));
        int pot = 1;
        for(int i=1;pot < n-1;pot++, i*=2) {
            dp1[pot-1][i] = adj[0][pot];
            dp2[pot-1][i] = adj[n-1][pot];
        }

        for(int i = 1;i<(1<<(n-2));i++) {
            for(int j = 0;j<n-2;j++) {
                if (!(i & (1<<j))) continue;
                for(int k=0;k<n-2;k++) {
                    if (i & (1 << k)) continue;
                    dp1[k][i|(1<<k)] = min(dp1[j][i] + adj[k+1][j+1], dp1[k][i|(1<<k)]);
                    dp2[k][i|(1<<k)] = min(dp2[j][i] + adj[k+1][j+1], dp2[k][i|(1<<k)]);
                }
            }
        }

        vector<int> comb(n-2);
        int hh = (n-1)/2;
        for(int i=0;i<hh;i++) {
            comb[i] = 1;
        }
        reverse(comb.begin(), comb.end());
        int ans = 1e9;
		// If exists just one hotel
        if (hh == n-2) ans = (adj[0][1] + adj[2][1]) * 2;
        do {
            int a1 = 1e9,a2 = 1e9;
            int numb = 0;
            int inv = 0;

            for(int i=0;i<n-2;i++) {
                numb += comb[i] << i;
                inv += (comb[i] == 0)<<i;
            }
            for(int j=0;j<n-2;j++) {
                if (!(numb & (1 << j))) continue;
                for(int k=0;k<n-2;k++) {
                    if (!(inv & (1 << k))) continue;
                    a1 = min(dp1[j][numb] + dp2[k][inv] + adj[j+1][k+1], a1);
                    a2 = min(dp2[j][numb] + dp1[k][inv] + adj[j+1][k+1], a2);
                    ans = min(ans, a1 + a2);
                }
            }
        } while(next_permutation(comb.begin(), comb.end()));

        cout <<"Case "<<++t<<": "<< ans << endl;

    }
    return 0;
}
