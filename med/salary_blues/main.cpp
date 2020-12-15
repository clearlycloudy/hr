#include <bits/stdc++.h>
#include <numeric>

using namespace std;

constexpr uint64_t M = 1'000'000'007;

// auto _gcd = []<typename T>(T a, T b){
//     auto gcd_impl = [](T a, T b, auto & f){
// 			if(a>b) swap(a,b);
// 			else if(a==0) return b;
// 			return f(b%a, a, f);
// 		    };
//     return gcd_impl(a,b, gcd_impl);
// };

int64_t _gcd(int64_t a, int64_t b){
    if(a>b) swap(a,b);
    if(a==0) return b;
    return _gcd(b%a, a);
};

int main(){
    int n,q;
    cin>>n>>q;
    vector<int64_t> arr(n);
    for(auto &i: arr){
	cin>>i;
    }
    //gcd(a,b,c)=gcd(a,b-a,c-a)
    //gcd(a+k,b+k,c+k)=gcd(a+k,b+k-a-k,...)=gcd(a+k,b-a,c-a)
    // int64_t g = reduce(arr.begin(),arr.end(), *arr.begin(), _gcd);
    int64_t g;
    if(arr.size()>1){
	g = abs(arr[1]-arr[0]);
    }else{
	g = arr[0];
    }
    for(int i=2; i<arr.size(); ++i){
	int64_t temp = abs(arr[i]-arr[0]);
	g = _gcd(g, temp);
    }
    
    for(int i=0;i<q;++i){
	int64_t k; cin>>k;
	// cout << "k: " << k << endl;
	int64_t gg;
	if(n>1){
	    gg = _gcd(arr[0]+k, g);
	}else{
	    gg = (arr[0]+k);
	}
	cout << gg << endl;
    }

    return 0;
}
