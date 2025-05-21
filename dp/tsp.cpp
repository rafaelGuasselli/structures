#include "../presets/base.cpp"

const int MAXN = 20;
int dp[MAXN][1<<MAXN], cost[MAXN][MAXN];

// Is necessary change too many things during the contest
// but, its a good base for the problem
int tsp (int n) {
  memset(dp, 0x3f, sizeof(dp));

  for(int i=0;i<n-1;i++) {
    dp[i][1 << i] = cost[0][i+1];
  }

  for(int i=1;i<1<<(n-1);i++){
    for(int j=0;j<n-1;j++) {
      if (!(i & (1 << j))) continue; // not visited yet
      int value = dp[j][i];
      int u = j + 1;
      for(int k =0;k<n-1;k++) {
        if ((i & (1 << k))) continue; // already visited
        int newmask = i|(1 << k);
        dp[k][newmask] = min(dp[k][newmask], value + cost[u][k+1]);
        }
    }
  }
  // INF
  int ans = INF;
  for(int i = 0;i<(n-1);i++){
    ans = min(ans, dp[i][(1<<(n-1))-1] + cost[i+1][0]);
  }

  return ans;
}
