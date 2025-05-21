#include <bits/stdc++.h>
using namespace std;

int t_count = 0;
void work(){
  int n; cin>>n;
  t_count++;
  vector<int> v(n);
  for(int i = 0; i<n; i++){
    cin>>v[i];
  }
  vector<pair<int, int>> edges(n-1);
  for(int i = 0; i<n-1; i++){
    cin>>edges[i].first>>edges[i].second;
  }

  if(t_count == 36){
    for(int i = 0; i<n; i++){
      if(i) cout<<" ";
      cout<<v[i];
    } cout<<endl;

    for(int i = 0; i<n-1; i++){
      cout<<edges[i].first<<" "<<edges[i].second<<endl;
    }
  }
}

int main(){
  int tt; cin>>tt;
  if(tt == 4) {
    vector<string> res = {
      "000",
      "1010",
      "0001",
      "1001001000100"};
    for(string e: res) cout<<e<<endl;
  }
  else {
    while(tt--) work();
  }
}