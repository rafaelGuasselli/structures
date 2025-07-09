#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define ll long long
using namespace std;

const int B = 64; // Word size (In this case, 64 bits for long long)

struct Gauss_xor{
	vector<ll> base; // store the number that acts as a base for each bit
	vector<vector<int>> table; // Can be used to retrieve what basis where involved in the xor
	int size = 0; // 2^size = num of different numbers
	Gauss_xor(){
		base.assign(B, 0);
		table.assign(B, vector<int>());
	}
	void insert(ll k){
		vector<int> aux;
		for(int i = B-1; i>=0; i--){ 
			if((k & (1LL << i)) == 0) continue;
			if(!base[i]) {
				base[i] = k, size++;
				table[i] = aux;
				return;
			}
			k ^= base[i];
			aux.push_back(i);
		}
	}

	// just some common uses, there are a lot more
	ll max_value(){
		ll k = 0;
		for(int i = B-1; i>=0; i--){
			if(!base[i]) continue;
			if((k & (1LL << i)) == 0) k ^= base[i];
		}
		return k;
	}
	bool exist(ll k){ // só retorna se existe ou não
		for(int i = B-1; i>=0; i--){
			if((k & (1LL << i)) != 0) k ^= base[i];
		}
		return k == 0;
	}
	ll count(ll k){ // Conta quantas vezes é possível criar um certo número.
		// só pensar na relação entre números dependentes e independentes.
		for(int i = B-1; i>=0; i--){
			if((k & (1LL << i)) != 0) k ^= base[i];
		}
		if(k) return 0; 
		return fast_pow(2, size_total-size); 
	}

};

int main(){
	int n; cin>>n;
	Gauss_xor g;
	for(int i = 0; i<n; i++){
		ll k; cin>>k;
		g.insert(k);
	}
}
