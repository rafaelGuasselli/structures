#include "geometry.cpp"
vector<point> seq;
int n; point translation;
void prepare(vector<point> &v){ // just garantee that the sorted points begin at the lowest (x, y)
	int pos = 0;
	n = v.size();
	for (int i = 1; i < n; i++) {
		if (v[i] < v[pos]) pos = i;
	}
	rotate(v.begin(), v.begin() + pos, v.end());
	n--;
	seq.resize(n);
	for (int i = 0; i < n; i++)
		seq[i] = v[i + 1] - v[0];
	translation = v[0];
}

bool pointInConvexPolygon(point p){  
	// must be a sorted convex polygon.
	p = p - translation;
	if (cross(seq[0], p) != 0 &&
			sgn(cross(seq[0], p)) != sgn(cross(seq[0], seq[n-1])))
		return false;
	if (cross(seq[n-1], p) != 0 &&
			sgn(cross(seq[n-1], p)) != sgn(cross(seq[n-1], seq[0])))
		return false;
	if (cross(seq[0], p) == 0)
		return dot(seq[0], seq[0]) >= dot(p, p);

	int l = 0, r = n-1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		int pos = mid;
		if (cross(seq[pos], p) >= 0)
			l = mid;
		else
			r = mid;
	}
	int pos = l;
	return pointInTriangle(seq[pos], seq[pos + 1], point::origin, p);
}