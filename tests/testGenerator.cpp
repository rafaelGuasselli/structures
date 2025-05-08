#include <bits/stdc++.h>
using namespace std;

int main(){
	int n = 1e4;
	cout<<"1"<<endl;
	cout<<n<<endl;
	for(int i = 1; i<=n; i++){
		if(i > 1) cout<<" ";
		cout<<rand()%n + 1;
	} cout<<endl;
	for(int i = 2; i<=n; i++){
		cout<<i/2<<" "<<i<<endl;
	}
}