#include "../presets/base.cpp"
struct Kuhn{

  // Para grafos bipartidos
  int n, k; // n = primeira partição, k = segunda partição
  vector<vector<int>> g; // Lista de adjecências da primeira partição para a segunda. 
  // Escolher a menor delas como a primeira durante a leitura.
  vector<int> mt;
  vector<bool> used;
  
  bool try_kuhn(int v) {
    if (used[v])
    return false;
    used[v] = true;
    for (int to : g[v]) {
      if (mt[to] == -1 || try_kuhn(mt[to])) {
        mt[to] = v;
        return true;
      }
    }
    return false;
  }
  
  void kuhn(){
    mt.assign(k, -1);
    vector<bool> used1(n, false);
    for (int v = 0; v < n; ++v) {
      for (int to : g[v]) {
        if (mt[to] == -1) {
          mt[to] = v;
          used1[v] = true;
          break;
        }
      }
    }
    for (int v = 0; v < n; ++v) {
      if (used1[v])
        continue;
      used.assign(n, false);
      try_kuhn(v);
    }
    
    for (int i = 0; i < k; ++i)
      if (mt[i] != -1)
        // mt[i] tells what vertex of the first part is connected to the vertex i of the second part, or -1 if it's not connected.
        // So if you want the size of it, just count how many aren't -1.
        printf("%d %d\n", mt[i] + 1, i + 1);
  }
};