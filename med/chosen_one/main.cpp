#include <bits/stdc++.h>

using namespace std;

uint64_t gcd(uint64_t a, uint64_t b){
    if(a>b)
	swap(a,b);

    if(a==0){
	return b;
    }else{	
	return gcd(b%a, a);
    }
}

int main(){

    uint64_t n;
    cin >> n;

    vector<uint64_t> arr(n);
    vector<uint64_t> pre(n);
    vector<uint64_t> suf(n);
    for(auto &i: arr){
	cin >> i;
    }
    
    if(n==1){
	cout << arr[0]+1 << endl;
	return 0;
    }
       
    uint64_t v = 0;
    for(uint64_t i=0;i<n;++i){
	pre[i] = gcd(v, arr[i]);
	v = pre[i];
    }
    
    v = 0;
    for(uint64_t i=n-1;i--;){
	suf[i] = gcd(v, arr[i]);
	v = suf[i];
    }

    for(uint64_t i=1;i<n-1;++i){
	auto a = pre[i-1];
	auto b = suf[i+1];
	uint64_t c = gcd(a,b);
        if(arr[i] % c != 0){
	    cout << c << endl;
	    return 0;
	}
    }
    if(arr[0] % suf[1] != 0){
	cout << suf[1] << endl;
	return 0;
    }
    else if(arr[n-1] % pre[n-2] != 0){
	cout << pre[n-2] << endl;
	return 0;
    }

    assert(false);
    
    return 0;
}
