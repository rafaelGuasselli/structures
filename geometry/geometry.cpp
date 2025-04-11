#include <bits/stdc++.h>
#define ld long double
using namespace std;
const ld eps = 1e-9, inf = 1e9;
struct point{
	ld x, y;
	point(ld x = 0, ld y = 0): x(x), y(y){};
	static point origin;
	static point translat;
	friend point operator + (const point p, const point q) {
        return point(p.x + q.x, p.y + q.y);  }
    friend point operator - (const point p, const point q) { 
        return point(p.x - q.x, p.y - q.y);  }
    friend point operator * (const point p, const ld k) { 
        return point(p.x * k, p.y * k); }
    friend ld dot(const point p, const point q) {
        return p.x * q.x + p.y * q.y; }
    friend ld cross(const point p, const point q) {
        return p.x * q.y - p.y * q.x;  }
	friend ld dist(const point&p, const point& q) {
		return sqrt(dot(p, q)); }
	friend ld proj(const point&p, const point&q) {
		return dot(p, q)/(dist(p, q)); }
	bool operator < (const point&p) const{
		return x<p.x || (x == p.x && y<p.y); }
	static bool angle_cmp(const point&p, const point&q){
		auto op = p-translat; auto oq = q-translat;
		ld a = atan2l(op.y, op.x), b = atan2l(oq.y, oq.x);
		return a < b;}
	friend ostream& operator<<(ostream& os, const point& p) {
		os << p.x << ", " << p.y;
		return os;
	}
};
point point::origin(0, 0);
point point::translat(0, 0); // this could and probabily should be changed to the smallest (x, y) point.


struct point3d{
	ld x, y, z;
    point3d() {}
    point3d(ld x, ld y, ld z): x(x), y(y), z(z) {}
    friend point3d operator+(const point3d& p, const point3d &q) {
        return point3d(p.x+q.x, p.y+q.y, p.z+q.z); }
    friend point3d operator-(const point3d& p, const point3d &q) {
        return point3d(p.x-q.x, p.y-q.y, p.z-q.z); }
    friend point3d operator*(const point3d& p, ld q) {
        return point3d(p.x*q, p.y*q, p.z*q); }
    friend point3d operator/(const point3d& p, ld q) {
        return point3d(p.x/q, p.y/q, p.z/q); }
	friend ld dot(const point3d& p, const point3d& q) {
		return p.x * q.x + p.y * q.y + p.z*q.z; }
	friend point3d cross(const point3d& p, const point3d &q) {
		return point3d(p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, 
						p.x * q.y - p.y * q.x);}
};

struct halfplane{ // Same as a line, interpreted as a point A and a vector A->B
	point p, pq;
	ld angle;
	halfplane(){}
	halfplane(point a, point b): p(a), pq(b-a){
		angle = atan2l(pq.y, pq.x); }
	bool out(const point& r){
		return cross(pq, r - p) < -eps; }
	bool operator < (const halfplane &e) const{
		return angle < e.angle; }
	friend point intersection(const halfplane& s, const halfplane & t){
		ld alpha = cross((t.p - s.p), t.pq)/cross(s.pq, t.pq);
		return s.p + (s.pq * alpha); }
};

double area(const vector<point>& v){ // sorted polygon by angle
	double res = 0;
	for(int i = 0; i<v.size(); i++){
		point p = i ? v[i-1] : v.back();
		point q = v[i];
		res += (p.x - q.x) * (p.y + q.y);
	} return fabs(res)/2;
}
int sgn(ld val ){ return val > 0 ? 1 : (val == 0 ? 0 : -1);}

bool pointInTriangle(point a, point b, point c, point p) {
    ld s1 = abs(cross(b-a, c-a));
    ld s2 = abs(cross(a-p, b-p)) + abs(cross(b-p, c-p)) + abs(cross(c-p, a-p));
    return s1 == s2;
}