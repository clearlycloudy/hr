#include <bits/stdc++.h>
using namespace std;

constexpr int64_t M = 1000000007;

int64_t n_fact(int64_t n){
    int64_t ret=1;
    for(int64_t i=1; i<=n; ++i){
	ret = (ret*i) % M;
    }
    return ret;
}

int64_t pow_mod(int64_t base, int64_t exp){
    int64_t ret = 1;    
    while(exp){
	if(exp & 1){
	    ret = (ret * base) % M;
	}
	base = (base * base) % M;
	exp >>= 1;
    }
    return ret;
}

int main() {
    string s;
    cin >> s;
    unordered_map<char,int> fs;
    
    for(auto i: s){
	fs[i]++;
    }

    int count_odd = 0;
    unordered_map<char,int64_t> even_counts;
    for(auto [v,freq]: fs){
	even_counts[v] = freq / 2;
	if(freq%2!=0){
	    count_odd++;
	}
    }

    assert(count_odd<=1);

    int64_t evens = 0;
    for(auto [v, counts]: even_counts){
	evens += counts;
    }

    //events!/product_{for all i}(counts_i!)
   
    
    int64_t numer = n_fact(evens);

    int64_t denom = 1;
    for(auto [v, counts]: even_counts){
	denom = ( denom * n_fact(counts) ) % M;
    }
    
    int64_t ret = ( numer * pow_mod(denom, M-2) ) % M;

    cout << ret << endl;

    return 0;
}
