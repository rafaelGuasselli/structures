#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define area(V) V[0]*V[1]-V[2] 


struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

signed main(){
  cin.tie(0); ios_base::sync_with_stdio(0);
  int n; cin>>n;
  vector<vector<int>> v(n+1, vector<int>(3));

  for(int i = 1; i<=n; i++){
    cin>>v[i][0]>>v[i][1]>>v[i][2];
  }
  sort(v.begin(), v.end());

  LineContainer cht;
  vector<int> dp(n+1, 0);
  cht.add(0, 0);

  int maior = 0;
  for(int i = 1; i<=n; i++){
    dp[i] = area(v[i]) + cht.query(v[i][1]);
    cht.add(-v[i][0], dp[i]);

    maior = max(maior, dp[i]);
  }
  cout<<maior<<endl;
}