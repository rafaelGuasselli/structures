// QUESTION SPOJ BABTWR - Tower Of Babylon 
// TESTING: DP -> box_stacking

#include "../dp/box_stacking.cpp"

int main() {
	while(1) {
		int n;cin>>n;
		if (!n) break;

		vector<vector<int>> boxes;
		for(int i=0;i<n;i++) {
			int a,b,c;cin>>a>>b>>c;
			boxes.push_back({a,b,c});
		}
		cout << boxStacking(boxes) << endl;
	}
}