#include "../presets/base.cpp"

// We use the LIS idea of stacking values, finding the the largest height.
// As we can rotate the boxes and repeat them, we can get all permutations
// of height, lenght and depth and sort them to get the best order (a sequence
// that can maximize the stacking

int boxStacking(vector<vector<int>>& b_ext) {
  vector<vector<int>> boxes;
  for (auto box: b_ext) {
    boxes.push_back({box[0],box[1],box[2]});
    boxes.push_back({box[0],box[2],box[1]});
    boxes.push_back({box[1],box[0],box[2]});
    boxes.push_back({box[1],box[2],box[0]});
    boxes.push_back({box[2],box[0],box[1]});
    boxes.push_back({box[2],box[1],box[0]});
  }
  sort(boxes.rbegin(), boxes.rend());
  int n = boxes.size();
  // Use an array
  vector<int> dp(n, 0);
  int ans=0;
  
  for(int i=0;i<n;i++) {
    auto box = boxes[i]; 
    for(int j=0;j<i;j++) {
      if (box[0] < boxes[j][0] && box[1] < boxes[j][1]) {
        dp[i] = max(dp[j], dp[i]);
      }  
    }
    dp[i] += box[2];
    ans = max(ans, dp[i]);
  }

  return ans;
}
