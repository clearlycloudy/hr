#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t M = 1'000'000'007;

constexpr uint64_t pow_mod(uint64_t base, uint64_t expo){
    uint64_t ret = 1;
    while(expo>0){
	if(expo & 1){
	    ret = (ret * base) % M;
	}
	base = (base * base) % M;
	expo >>= 1;
    }
    return ret;
}

static_assert(pow_mod(2,1)==2);
static_assert(pow_mod(2,2)==4);
static_assert(pow_mod(2,3)==8);
static_assert(pow_mod(3,2)==9);
static_assert(pow_mod(3,3)==27);
static_assert(pow_mod(3,4)==81);

uint64_t fact(uint64_t x){
    uint64_t ret = 1;
    for(uint64_t i=1;i<=x;++i){
	ret = (ret * i) % M;
    }
    return ret;
}

int main(){
    uint64_t a,b;
    cin>>a>>b;
    uint64_t high = max(a,b);
    uint64_t low = min(a,b);
    uint64_t ret;
    if(high<25){
	cout << 0 << endl;
	return 0;
    }else if(high==25 && low<24){
	ret = fact(low+24);
	ret = (ret * pow_mod(fact(low), M-2)) % M; //divide by fact(low)
	ret = (ret * pow_mod(fact(24), M-2)) % M; //divide by fact(low)
    }else if(high>25 && high==low+2){
	ret = fact(24+24);
	ret = (ret * pow_mod(fact(24), M-2)) % M; //divide by fact(24)
	ret = (ret * pow_mod(fact(24), M-2)) % M; //divide by fact(23)
	if(low>24){
	    ret = (ret * pow_mod((uint64_t)2, (low-24)%M)) % M; //extra combinations for lock step score increments (2 possibilities for each incrementment)
	}
    }else{
	cout << 0 << endl;
	return 0;
    }
    cout << ret << endl;
    return 0;
}
