#include "../base.cpp"
string s, t;
int edit(int s1, int t1, vector<vector<int>> &memo){
	if(!t1) return s1;
	if(!s1) return t1;
	if(memo[s1][t1] != -1){
		return memo[s1][t1];
	}
	if(s[s1-1] == t[t1-1]){
		return memo[s1][t1] = edit(s1-1, t1-1, memo);
	}
	return memo[s1][t1] = 1 + min(min(edit(s1, t1-1, memo), edit(s1-1, t1, memo)), edit(s1-1, t1-1, memo));
}