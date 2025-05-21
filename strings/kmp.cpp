#include "../presets/base.cpp"
#include "prefix_function.cpp"
vector<int> kmp(string &t, string &p){
  vector<int> lps = prefix_function(t);
  int i = 0, j = 0;
  vector<int> res;
  while (i < t.size()) {
    if (t[i] == p[j]) {
      i++, j++;
      if (j == p.size()) {
        res.push_back(i-j);
        j = lps[j-1];
      }
    } else {
      if (j != 0) {
        j = lps[j-1];
      } else {
        i++;
      }
    }
  }
  return res;
}