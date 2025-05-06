#include "../base.cpp"
struct SparseTable {
    vector<vector<int>> st;
	vector<int> log;
	int n, k;
    SparseTable(vector<int> &a) {
		n = a.size();
		k = log2(n)+1;
        st.assign(k, vector<int>(n));
		copy(a.begin(), a.end(), st[0]);
		log.assign(n+1, 0);
		for(int i = 2; i<=n; i++) log[i] = log[i/2]+1;
		// It's possible to construct the st with any operation that satisfies f((a, b), c) = f(a, (b, c))
		// just switch the min for the desired function
        for (int i = 1; i <= k; i++)
            for (int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
    int query(int l, int r) {
        int i = log2(r - l + 1);
        return min(st[i][l], st[i][r - (1 << i) + 1]);
    }
	int sum_query(int l, int r){
		int sum = 0;
		for (int i = k; i >= 0; i--) {
			if ((1 << i) <= r - l + 1) {
				sum += st[i][l];
				l += 1 << i;
			}
		}
		return sum;
	}
};