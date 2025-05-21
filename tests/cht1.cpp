#include <bits/stdc++.h>
#define int long long
#define INF 10e9
using namespace std;
#define area(V) V[0]*V[1]-V[2] 

struct line {
    int m, b;
	line(int a, int k): m(a), b(k){};
    
	int operator()(int x)
    {
        return m * x + b;
    }
};

const int MAXN = 1e6+2;

vector<line> a(MAXN * 4);

void init(){
	for(int i = 0; i<4*MAXN; i++){
		a[i] = line(0, INF);
	}
}

void insert(int l, int r, line segment, int idx = 0){
    if (l + 1 == r) {
        if (segment(l) > a[idx](l))
            a[idx] = segment;
        return;
    }
    int mid = (l + r) / 2;
    int leftson = idx * 2 + 1, rightson = idx * 2 + 2;
    if (a[idx].m > segment.m)
        swap(a[idx], segment);
    if (a[idx](mid) < segment(mid)) {
        swap(a[idx], segment);
        insert(l, mid, segment, leftson);
    }
    else
        insert(mid, r, segment, rightson);
}

int query(int l, int r, int x, int idx = 0){
    if (l + 1 == r)
        return a[idx](x);
    int mid = (l + r) / 2;
    int leftson = idx * 2 + 1;
    int rightson = idx * 2 + 2;
    if (x < mid)
        return max(a[idx](x), query(l, mid, x, leftson));
    else
        return max(a[idx](x), query(mid, r, x, rightson));
}

signed main(){
	cin.tie(0); ios_base::sync_with_stdio(0);
	int n; cin>>n;
	vector<vector<int>> v(n+1, vector<int>(3));

	for(int i = 1; i<=n; i++){
		cin>>v[i][0]>>v[i][1]>>v[i][2];
	}
	sort(v.begin(), v.end());
	init();

	vector<int> dp(n+1, 0);
	insert(0, MAXN, line(0, 0));

	int maior = 0;
	for(int i = 1; i<=n; i++){
		dp[i] = area(v[i]) + query(0, MAXN, v[i][1]);
		insert(0, MAXN, line(-v[i][0], dp[i]));

		maior = max(maior, dp[i]);
	}
	cout<<maior<<endl;
}