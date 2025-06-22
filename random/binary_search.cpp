// not so useful to know
int binary_search(){
	int l = 0, r = 1e18;
	while(l < r){
		int m = l + (r-l)/2;
		if(true) r = m;
		else l = m+1; // this finds the first false position, upper_bound
	}
}
int binary_search2(){
	int l = 0, r = 1e18;
	while(l < r){
		int m = l + (r-l+1)/2;
		if(true) r = m-1;
		else l = m; // this should find the last true position, lower_bound
	}
}