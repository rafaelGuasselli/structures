#define MAX 1000000
bitset<MAX+1> b;
void sieve(){
	b.set();
	b[0] = b[1] = false;
	for(int i = 2; i*i<=MAX; i++){
		if(b[i])
			for(int p = i*i; p <= MAX; p+=i){
				b[p] = false;
			}
	}
}
