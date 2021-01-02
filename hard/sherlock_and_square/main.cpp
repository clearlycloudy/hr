#include<bits/stdc++.h>

using namespace std;

uint64_t M = 1000'000'007;

uint64_t mypow(uint64_t base, uint64_t expo){
    uint64_t ret = 1;
    while(expo){
	if(expo & 1){
	    ret = (ret * base) % M;
	}
	base = (base * base) % M;
	expo = expo >>= 1;
    }
    return ret;
}
int main(){
    int t; cin >> t;
    for(int i=0;i<t;++i){
	int n; cin >> n;
	//sum_{i=1..n}(2^i) = sum_{i=0..n}(2^i) - 1 = (1-2^(n+1))/(1-2) - 1 = 2^(n+1)-2
	//4 + sum_{i=1..n}(2^i) = 4 + 2^(n+1)-2 = 2 + 2^(n+1)
	cout << 2 + mypow(2,n+1) << endl;
    }
    return 0;
}
