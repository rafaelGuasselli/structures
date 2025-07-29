#include "../presets/base.cpp"

// Tem alguma coisa errada aqui

vector<int> prefix_function(string &s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i-1];
    while (j > 0 && s[i] != s[j])
      j = pi[j-1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

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
