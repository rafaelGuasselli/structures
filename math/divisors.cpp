#include "../presets/base.cpp"
// Get all divisors via a map with the prime factors
// Probably could be done better.
set<int> divisors(int n){
	set<int> d;
	for(int i = 1; i*i <=n ; i++){
		if(n % i == 0) d.insert(i);
	}
	vector<int> v;
	for(int e: d){
		v.push_back(n/e);
	}
	for(int e: v) d.insert(e);
}