#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <functional>

using namespace std;

long long const M = 1000000007;

long long const H = 10000000;
vector<long long> fact_mem(H);

inline long long fac( long long n ){
    return fact_mem[n];
}

//fast exponentiation with modulo
long long degree(long long a, long long k, long long p) {
    long long res = 1;
    long long cur = a;

    while (k) {
	if (k % 2) {
	    res = (res * cur) % p;
	}
	k /= 2;
	cur = (cur * cur) % p;
    }
    return res;
}

void solve( vector<vector<int> > & t, vector<long long> & permute_child, vector<int> & child_counts, int cur ){

    int l = t[cur].size();

    for( int i = 0; i<l; ++i) {
	int idx = t[cur][i];
	solve( t, permute_child, child_counts, idx ); //recurse for post order
    }
	
    long long dp = 1;
    long long sum_children = 0;
    long long denominator = 1;
    for( int i = 0; i<l; ++i) {
	int idx = t[cur][i];
	sum_children += child_counts[idx];
	denominator = ( denominator * fac( child_counts[idx] ) ) % M;
        dp = ( dp * permute_child[idx] ) % M;
	child_counts[cur] += child_counts[idx];
    }
    long long numer = fac(sum_children);
    //fermat's little theorem says if p is prime, a^(p-1) = 1 (mod p)
    //in this case, p = M is a prime
    //a*a^(p-2) = 1 (mod p)
    //thus a^(-1) = a^(p-2) (mod p)
    long long y = ( numer * degree( denominator, M-2,  M ) ) % M;
    permute_child[cur] = ( dp * y ) % M;
}

int main() {

    fact_mem[0]=1;
    for( long long i = 1; i < H; ++i ){
	fact_mem[i] = (i * fact_mem[i-1] ) % M;
    }

    int tc;
    cin >> tc;

    vector<int> rel(200000,-1); //map: e->b
    vector<int> disjoint(200000);
    unordered_set<int> disjoint_roots;
    vector<long long> permute_child(200000,1);
    vector<int> child_count(200000+1,1);
    vector<long long> combos(200000+1,1);
	
    for(int i = 0; i < tc; i++){

	int n,m;
	cin >>n>>m;

	//init
	vector< vector<int> > topdown(n+1, vector<int>{} ); //map: b->[e]
	disjoint_roots.clear();
	std::fill(permute_child.begin(), permute_child.begin()+n, 1);
	std::fill(child_count.begin(), child_count.begin()+n+1, 1);
	std::fill(combos.begin(), combos.begin()+n+1,1);
	std::fill(rel.begin(), rel.begin()+n,-1);
	for(int j = 0; j < n; ++j){
	    disjoint[j] = j;
	}

	//build
	for(int j = 0; j < m; ++j){
	    int b, e;
	    cin >> b >> e;
	    --b; --e;
	    rel[e] = b;
	    disjoint[e]=b;
	    topdown[b].push_back(e);
	}

	for(int j = 0; j <n; ++j){
	    if (disjoint[j] == j ) {
		disjoint_roots.insert(j);
	    }
	}

	int root = n;
	for( auto j : disjoint_roots ){
	    topdown[root].push_back(j);
	}

	solve( topdown, combos, child_count, root );

	cout << combos[root] << endl;
    }

    return 0;
}
