#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

constexpr long long M = 1000'000'007;

long long fac(long long in){
    long long ret = 1;
    for(long long i = 2; i <= in; ++i){
	ret = (ret * i) % M;
    }
    return ret;
}

long long exponent(long long base, long long exp){
    
    if(exp==0){
	return 1;
    }
	
    long long ans = 1;
    base = base % M;
    
    while(exp!=0){
	if(exp % 2 == 1){
	    ans = (base * ans) % M;
	}
	exp = exp >> 1;
	base = (base * base) % M;
    }

    return ans;
}

long long choose(long long n, long long r){
    
    long long ans = 1;
    
    for(long long i = 0; i < r; ++i){
	ans = (ans * (n-i)) % M;
    }
    
    //fermat's theorem
    ans = (ans * exponent(fac(r), M-2)) % M;
    
    return ans;
}

long long compute_(long long count_orig, long long count, long long rows_max){
    
    if(rows_max==1){
	cout << "rows_max: " << rows_max << ", return: " << 1 << endl;
	return 1;
    }
    
    if(count==1){
	return rows_max;
    }
    
    long long accum = 0;

    for(long long k = 1; k <= rows_max; ++k){
    // long long k = rows_max;
    // {
	long long r = count % k; //let r be the remaining items

	long long b = count_orig == count ? 1 : 0;
	
	long long num_columns = count/k;
	// if(k==1 || k == count){ //only 1 row remaining
	//     long long temp = 1;
	//     accum = (accum + temp) % M;
	//     // cout << "count: " << count << ", k: " << k << ", compute: " << temp << endl;
	// }else{ //more than 1 row
	    long long h = num_columns;

	    long long left_over = (num_columns-h)*k + r;
	    assert(left_over>=0);
	    long long temp = (((exponent(fac(k), h-b) * choose(rows_max,k))%M) * compute_(count_orig, left_over, k-1)) % M;
	    // cout << "count: " << count << ", k: " << k << ", h: " << h << ", r: " << r << ", left_over: " << left_over << ", compute: " << temp << endl;
	    
	    accum = (accum + temp) % M;
	// }
    }
    return accum;
}

int main() {

    // assert(exponent(2,3)==8);
    // assert(fac(4)==24);
    // assert(choose(4,2)==6);
    
    int t;
    cin >> t;
    for(int i=0; i<t; ++i){
	int n;
	cin >> n;	
	vector<int> arr(n,0);
	for(auto&j:arr){
	    cin >> j;
	}

	vector< vector<int> > dp(2, vector<int>(2,0));
	
	for(int j = 1; j <n; ++j){ //O(n)
	    vector<int> nums0 { 1, arr[j-1] };
	    vector<int> nums1 { 1, arr[j] };
	    for(int idx0 = 0; idx0<2; ++idx0){
		for(int idx1 = 0; idx1<2; ++idx1){
		    int m = nums0[idx0];
		    int k = nums1[idx1];
		    int weight = abs(m-k);
		    dp[1][idx1] = max(dp[1][idx1], dp[0][idx0] + weight);
		    
	    	}
	    }
	    dp[0].swap(dp[1]);
	}//total: O(4*n)

	int ans = max(dp[0][0], dp[0][1]);
	printf("%d\n",ans);
    }

    fflush(stdout);

    return 0;
}
