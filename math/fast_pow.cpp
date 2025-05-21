#include "../presets/base.cpp"
#define md 1000000007
int fast_pow(int a, int b){ // Same logic (and almost the same code) can be applied 
							// to all comutative and associative operations, sum, gcd, etc...
 	int res = 1;
 	while(b){
 		if(b & 1){
 			res = (a*b)%md;
 		}
 		a = (a*a)%md;
 		b >>=1;
 	}
 	return res;
 }
