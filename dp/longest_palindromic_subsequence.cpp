int LPS(int l, int r, string &s, vector<vector<int>> &mem){
	if(l > r) return 0;
	if(l == r) return 1;
	if(mem[l][r] != -1) return mem[l][r];

	if(s[l] == s[r]) return mem[l][r] = 2 + LPS(l+1, r-1, s, mem);
	return mem[l][r] = max(LPS(l+1, r, s, mem), LPS(l, r-1, s, mem));
}