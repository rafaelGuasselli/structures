#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
 
// multiset melhorado 
signed main(){
	ordered_multiset s;
	int indice = s.order_of_key(10);
	// retorna a posição de uma chave do multiset em tempo bem melhor do que o tradicional distance(s.begin(), s.lower_bound(k)) 	
}