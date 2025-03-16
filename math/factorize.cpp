// Faster option: while(a % 2) and while(a % 3) first
// and after that i = 5, i+=6, (a % i) and (a % (i+2))
void factorize(int a, map<int, int> &factors){
	for(int i = 2; i*i<=a; i++){
		while(a%i == 0){
			factors[i]++;
			a/=i;
		}
	}
	if(a > 1) factors[a]++;
}