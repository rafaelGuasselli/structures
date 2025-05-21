// QUESTION 253 CODEFORCES - Theodore Roseevelt
// TESTING: Geometry -> pointInConvexPolygon
#include "../geometry/pointInConvexPolygon.cpp"
// In actual contest, instead of include, the partial/whole code should
// be hard coded in the file. 
int main(){
  int n, m, k; cin>>n>>m>>k;
  vector<point> p(n); // the input is already ordered
  for(int i = 0; i<n; i++){
    int p1, p2; cin>>p1>>p2;
    p[i] = {(ld)p1, (ld)p2};
  }
  int count = 0;
  prepare(p); // makes a translation for every point of polygon
  for(int i = 0; i<m; i++){
    int q1, q2; cin>>q1>>q2;
    point q(q1, q2);
    if(pointInConvexPolygon(q)) count++;
  }
  if(count >= k) cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
}