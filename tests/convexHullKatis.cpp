// QUESTION CONVEX HULL FROM KATTIS, FUNCTIONING.
#include <bits/stdc++.h>
#define ld int
using namespace std;

const ld eps = 1e-9, inf = 1e9;

struct point {
  ld x, y;
  point(ld x = 0, ld y = 0) : x(x), y(y) {}
  static point origin;
  static point translat;

  friend point operator+(const point p, const point q) {
    return point(p.x + q.x, p.y + q.y);
  }
  friend point operator-(const point p, const point q) {
    return point(p.x - q.x, p.y - q.y);
  }
  friend point operator*(const point p, const ld k) {
    return point(p.x * k, p.y * k);
  }
  friend ld dot(const point p, const point q) {
    return p.x * q.x + p.y * q.y;
  }
  friend ld cross(const point p, const point q) {
    return p.x * q.y - p.y * q.x;
  }
  bool operator<(const point &p) const { // Return smallest (x, y)
    return x < p.x || (x == p.x && y < p.y);
  }
  static bool smallest_y(const point&p, const point&q){
    return p.y < q.y || (p.y == q.y && p.x < q.x);
  }
  friend int orientation(const point &p, const point &q) {
    ld o = cross(p, q);
    if (o < 0) return -1; // clockwise
    if (o > 0) return 1;  // counter clockwise
    return 0;       // collinear
  }
  static bool ccw_cmp(const point&p, const point &q){
    point v1 = p-translat;
    point v2 = q-translat;
    int o = orientation(v1, v2);
    if(o == 0){
      return dot(v1, v1) < dot(v2, v2);
    }
    return o > 0;
  }
  bool operator==(const point &p) {
    return (x == p.x && y == p.y);
  }
  friend bool collinear(point &a, point &b, point &c) {
    return orientation(a - c, b - c) == 0;
  }
  friend ostream &operator<<(ostream &os, const point &p) {
    os << p.x << " " << p.y;
    return os;
  }
};
point point::origin(0, 0);
point point::translat(0, 0);

struct Convex_hull{
  static bool ccw(const point&a, const point&b, const point&c, bool include_collinear){
    int o = orientation(b-a, c-a);
    return o > 0 || (include_collinear && o == 0);
  }
  static void graham_scan(vector<point> &a, bool include_collinear = false){
    point p0 = *min_element(a.begin(), a.end(), point::smallest_y);
    point::translat = p0;
    sort(a.begin(), a.end(), point::ccw_cmp);
    if(include_collinear){
      int i = (int)a.size()-1;
      while(i >= 0 && collinear(p0, a[i], a.back())) i--;
      reverse(a.begin()+i+1, a.end());
    }
    vector<point> st;
    for(int i = 0; i<(int)a.size(); i++){
      while(st.size() > 1 && !ccw(st[st.size()-2], st.back(), a[i], include_collinear))
        st.pop_back();
      st.push_back(a[i]);
    }

    if(include_collinear == false && st.size() == 2 && st[0] == st[1])
      st.pop_back();
    
    a = st;
  }
};

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  while(true){
    int n; cin>>n;
    if(!n) break;

    vector<point> p(n);
    for(int i = 0; i<n; i++){
      int a, b; cin>>a>>b;
      p[i]= point(a, b);
    }

    Convex_hull::graham_scan(p);
    cout<<p.size()<<endl;
    for(auto e: p){
      cout<<e<<endl;
    }
  }

}