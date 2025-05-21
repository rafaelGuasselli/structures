#include "../presets/base.cpp"
// Get all divisors via a map with the prime factors
// Probably could be done better.
void divisors(map<int, int> &factors, set<int> &d){
	d.clear(); d.insert(1);
    for(auto e: factors){
        int p = e.first;
        int exp = e.second;
        vector<int> aux;
        for(auto c : d){
            long long temp = 1;
            for(int i = 0; i < exp; i++){
                temp *= p;
                aux.push_back(c * temp);
            }
        }
        for(auto v : aux) d.insert(v);
    }
}