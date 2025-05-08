#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
	return a + rand()%(b - a + 1);
}
// Generate a random input for the sh script. Should be modified based on the real problem.
int main(int argc, char *argv[]){
	srand(atoi(argv[1]));
	int n = rand(2, 5000);
	printf("%d\n", n);
	set<int> used;
	for(int i = 0; i<n; i++){
		int x;
		do {
			x = rand(1, 5000);
		} while(used.count(x));
		printf("%d ", x);
		used.insert(x);
	}
	puts("");
}