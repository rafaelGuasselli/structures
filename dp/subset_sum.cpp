vector<vector<bool>> dp(n+1, vector<bool>(max_sum+1, false));
dp[0][0] = true;
for(int j = 0; j<=max_sum; j++){
  for(int i = 1; i<=n; i++){
    dp[i][j] = dp[i-1][j] || (j >= w[i-1] ? dp[i-1][j-w[i-1]] : 0);
  }
}