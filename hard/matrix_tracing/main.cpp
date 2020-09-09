#include <cassert>
#include <climits>
#include <cstdint>
#include <cstring>
#include <utility>
#include <iostream>

using namespace std;

constexpr int64_t M = 1'000'000'007;

int64_t factorial(int64_t in){
    int64_t ret = 1;
    for(int64_t i=1;i<=in;++i)
	ret = (ret * (i % M)) % M;
    return ret;
}

int64_t exponent_mod(int64_t base, int64_t power, int64_t mod){
    int64_t ret = 1;
    while(power){
	if(power & 1)
	    ret = (ret * base) % mod;
	power >>= 1;
	base = (base * base) % mod;
    }
    return ret;
}

int64_t solve(int n, int m){

    //from pascal triangle, calculate row and col
    if(n<m) swap(n,m);
    
    int nn = n-1;
    int mm = m-1;
    int row = nn+mm;
    int col = mm;
    assert(row>=col);

    //answer is row choose col
    //row!/((row-col)!col!)
    auto a = factorial(row);
    auto b = (factorial(col) * factorial(row-col)) %M;
    //1 = x^(p-1) % p, for p prime
    //x^(-1) = x^(p-2) % p
    return (a * exponent_mod(b, M-int64_t(2), M)) % M;
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;++i){
	int n,m;
	cin>>n>>m;
	cout << solve(n,m) << endl;
    }
    
    return 0;
}
    
