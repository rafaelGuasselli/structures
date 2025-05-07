#include "geometry.cpp"
// From geometry using: Point, point::orientation, 
struct Convex_hull{
	static bool cw(const point&a, const point&b, const point&c, bool include_collinear){
		// Easy to change to ccw, just change all the calls of cw to ccw
		int o = orientation(a-c, b-c);
		return o < 0 || (include_collinear && o == 0);
	}
	friend void graham_scan(vector<point> &a, bool include_collinear = false){
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