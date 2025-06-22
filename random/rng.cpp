#include "../presets/base.cpp"
//	STRONG RANDOM GENERATION
random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> dist(1, 3); // 1, 3 incluse range
	
int main(){
	cout<<dist(rng)<<endl; 
	// returns random number between 1 and 3 with equal chance distribution.
}