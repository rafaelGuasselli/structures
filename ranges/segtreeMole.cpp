struct Node{
	int lb, rb, s;
	Node(int a, int b, int c): lb(a), rb(b), s(c) {}
	Node(){}
};
 
class SegTree{
private:
  int n;
  vector<Node> A, St;
 
  int rl(int p) {return p<<1;}
  int rr(int p) {return (p<<1)+1;}
 
  
  Node conquer(Node a, Node b) {
	auto [a1, b1, c1] = a;
	auto [a2, b2, c2] = b;
	int t = min(a1, b2);
	Node k(a1+a2-t, b1+b2-t, c1+c2+t);
	return k;
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
 
 
  Node RSQ(int i, int l, int r, int tl, int tr) {
    if (l > tr || r < tl) return {0, 0, 0};
    if ((l <= tl) && (r >= tr)) return St[i];
    int mid = (tl+tr)/2;
    return conquer(RSQ(rl(i), l , r, tl, mid), RSQ(rr(i), l, r, min(tr,mid+1), tr));
  }
 
  void update(int i, int l, int r, int tl, int tr, Node x) {
	if (l > tr || r < tl) return;
	if ((l <= tl) && (r >= tr)) {
		St[i] = x;
		return;
	}
	int mid = (tl + tr) / 2;
	update(rl(i), l, r, tl, mid, x);
	update(rr(i), l, r, min(mid+1, tr), tr, x);
	St[i] = conquer(St[rl(i)], St[rr(i)]);
  }
 
