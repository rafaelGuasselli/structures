#include "../presets/base.cpp"
// Lis O(n log k) 
void print_LIS(vector<int> &P, vector<int> &A, int i) {
  if (P[i] == -1) cout << A[i];
  print_LIS(P, A, P[i]);
  cout <<" "<<A[i];
}

int  n,k = 0; // n is the number of elements and k is the length length of actual LIS.
vector<int> L(n,0), L_id(n), p(n);
// L has the values of the last element of LIS with length i
// L_id is the position of the element L[i] in original array 
// P is the position of the element that addded before this 
// number.
// If we just need the length of the LIS, the vectors L_id and p are unnecessary
int lis(vector<int> &A){
  for (int i = 0; i < n; ++i) {          // O(n)
    int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
    L[pos] = A[i];                 
    L_id[pos] = i;                 
    p[i] = pos ? L_id[pos-1] : -1;         
    if (pos == k) {                
    k = pos+1;                 
    }
  }
}