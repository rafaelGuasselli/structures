
#include <bits/stdc++.h>
using namespace std;

struct point {
	double x, y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	
	static point translat;
	friend double cross(const point p, const point q) {
		return p.x * q.y - p.y * q.x;
	}

	static bool smallest_y(const point&p, const point&q){
    	return p.y < q.y || (p.y == q.y && p.x < q.x);
    }

	friend double dot(const point p, const point q) {
		return p.x * q.x + p.y * q.y;
	}
	friend bool collinear(point &a, point &b, point &c) {
    	return orientation(a - c, b - c) == 0;
  	}

	friend int orientation(const point &p, const point &q) {
		double o = cross(p, q);
		if (o < 0) return -1; // clockwise
		if (o > 0) return 1;  // counter clockwise
		return 0;       // collinear
	}
	friend point operator-(const point p, const point q) {
		return point(p.x - q.x, p.y - q.y);
	}

	static bool cw_cmp(const point&p, const point &q){
		point v1 = p-translat;
		point v2 = q-translat;
		int o = orientation(v1, v2);
		if(o == 0){
			return dot(v1, v1) < dot(v2, v2);
		}
		return o < 0;
	}
	bool operator==(const point &p) {
    	return (x == p.x && y == p.y);
  	}
	friend ostream &operator<<(ostream &os, const point &p) {
		os << p.x << ", " << p.y;
		return os;
	}
};
point point::translat(0, 0);

// From geometry using: Point, orientation, cross, smallest_y, cw_cmp, dot, operator-, operator==, translat
struct Convex_hull{
  static bool cw(const point&a, const point&b, const point&c, bool include_collinear){
    // Easy to change to ccw, just change all the calls of cw to ccw
    int o = orientation(a-c, b-c);
    return o < 0 || (include_collinear && o == 0);
  }
  static void graham_scan(vector<point> &a, bool include_collinear = false){
    point p0 = *min_element(a.begin(), a.end(), point::smallest_y);
    point::translat = p0;
    sort(a.begin(), a.end(), point::cw_cmp);
    // Often it will be requested to sort ccw, so just change the algorithm for that and it already works.
    if(include_collinear){ 
      int i = (int)a.size()-1;
      while(i >= 0 && collinear(p0, a[i], a.back())) i--;
      reverse(a.begin()+i+1, a.end());
    }
    vector<point> st;
    for(int i = 0; i<(int)a.size(); i++){
      while(st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
        st.pop_back();
      st.push_back(a[i]);
    }
    if(include_collinear == false && st.size() == 2 && st[0] == st[1])
      st.pop_back();
    a = st;
  }
};

int n;
double d, e;

double dist(point &a, point &b) {
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}
int main() {
	cin>>n;
	vector<point> p(n);
	point C(0, 0);

	for (int i = 0; i < n; i++) {
		cin>>p[i].x>>p[i].y;
		C.x += p[i].x; C.y += p[i].y;
	}
	C.x /= n; C.y /= n;

	Convex_hull::graham_scan(p, true);
	n = p.size();
	
	double P = 0.1;
	double last = d;
	int count = 0;
	point C_last = C;
	for (int i = 0; i < 1000000; i++) {
		int f = 0;
		d = dist(C, p[0]);
		for (int j = 1; j < n; j++) {
			e = dist(C, p[j]);
			if (d < e) { d = e; f = j; }
		}
		C.x += (p[f].x - C.x)*P;
		C.y += (p[f].y - C.y)*P;
		P *= 0.999;
		if(d == last || C == C_last) count ++;
		else count = 0;
		if(count > 1000) break;
		last = d;
		C_last = C;
	}
	printf("%.2lf %.2lf %.2lf %.2lf\n", C.x, C.y, sqrt(d), 8*sqrt(d)*3.14);
}