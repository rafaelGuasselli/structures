#include <bits/stdc++.h>
#define ld long double
using namespace std;
const ld eps = 1e-9, inf = 1e9;

struct point{
	ld x, y;
	point(ld x = 0, ld y = 0): x(x), y(y){};
	friend point operator + (const point& p, const point& q) {
        return point(p.x + q.x, p.y + q.y); 
    }
    friend point operator - (const point& p, const point& q) { 
        return point(p.x - q.x, p.y - q.y); 
    }
    friend point operator * (const point& p, const ld& k) { 
        return point(p.x * k, p.y * k); 
    } 
    friend ld dot(const point& p, const point& q) {
        return p.x * q.x + p.y * q.y;
    }
    friend ld cross(const point& p, const point& q) { 	
        return p.x * q.y - p.y * q.x; 
    }
};

struct halfplane{
	point p, pq;
	ld angle;
	halfplane(){}
	halfplane(point a, point b): p(a), pq(b-a){
		angle = atan2l(pq.y, pq.x);
	}
	bool out(const point& r){
		return cross(pq, r - p) < -eps;
	}
	bool operator < (const halfplane &e) const{
		return angle < e.angle;
	}
	friend point intersection(const halfplane& s, const halfplane & t){
		ld alpha = cross((t.p - s.p), t.pq)/cross(s.pq, t.pq);
		return s.p + (s.pq * alpha);
	}
};