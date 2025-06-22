// Just a sweep line
#include "../presets/base.cpp"
int sweepLine(vector<pair<int, int>> &v){
	sort(all(v));
	int res = 0, l = -1e9, r = -1e9;
	for (auto [x, y] : v) {
		if (x > r) res += r - l, l = x; // +1 in r-l makes inclusive range
		r = max(r, y);
	}
	res += r - l;
	return res;
}