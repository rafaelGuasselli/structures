// To change the operation, just change conquer and RSQ and propagate
class SegTree{
private:
    int n;
    vector<ll> A, St, Lazy;

    int rl(int p) {return p<<1;}
    int rr(int p) {return (p<<1)+1;}

    
    ll conquer(ll a, ll b) {
        return a+b;
    }

    void build(int i, int l, int r) {
        if(l == r) {
            St[i] = A[l];
        } else {
            int mid = (l+r)/2;
            build(rl(i), l, mid);
            build(rr(i), mid+1, r);
            St[i] = conquer(St[rl(i)], St[rr(i)]);
        }
    }

    void propagate(int i, int l, int r) {
        if (Lazy[i] != -1) {
            St[i] = Lazy[i] * (r - l + 1);
            if (l != r) { Lazy[rl(i)] = Lazy[rr(i)] = Lazy[i]; }
            else { A[l] = Lazy[i]; }
            Lazy[i] = -1;
        }
    }

    ll RSQ(int i, int l, int r, int tl, int tr) {
        propagate(i, tl, tr);
        if (l > tr || r < tl) return 0;
        if ((l <= tl) && (r >= tr)) return St[i];
        int mid = (tl+tr)/2;
        return conquer(RSQ(rl(i), l , r, tl, mid), RSQ(rr(i), l, r, min(tr,mid+1), tr));
    }

    void update(int i, int l, int r, int tl, int tr, int x) {
        propagate(i, l, r);
        if (l > tr || r < tl) return;
        if ((l <= tl) && (r >= tr)) {
            Lazy[i] = x;
            propagate(i, tl, tr);
        } else {
            int mid = (tl + tr) / 2;
            update(rl(i), l, r, tl, mid, x);
            update(rr(i), l, r, min(mid+1, tr), tr, x);
            St[i] = St[rl(i)] + St[rr(i)];
        }
    }

public:
    SegTree(int sz): n(sz), St(4*n), Lazy(4*n, -1) {}
    SegTree(const vector<ll> &initial):SegTree(initial.size()) {
        A = initial;
        build(1, 0, n-1);
    }

    void update(int i, int j, int val) { update(1,i,j, 0,n-1, val);}
    ll RSQ(int i, int j) { return RSQ(1, i,j,0,n-1);}
};
