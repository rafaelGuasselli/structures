#include "../base.cpp"

int editDistance(string a, string b) {
	if (a.size() > b.size()) swap(a,b);
	int n = a.size(), m =b.size();

	vector<vector<int>> dp_(n+1, vector<int>(m+1, 0));
	for(int i=0;i<=n;i++) {
		dp_[i][0] = i;
	}
	for(int i=0;i<=m;i++) {
		dp_[0][i] = i;
	}
	
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if (a[i-1] == b[j-1]) {
				dp_[i][j] = dp_[i-1][j-1];
			} else {
				dp_[i][j] = min({dp_[i-1][j], dp_[i][j-1], dp_[i-1][j-1]}) + 1;
			}
		}
	}

	return dp_[n][m];
}
