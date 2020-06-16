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

    assert(exponent(2,3)==8);
    assert(fac(4)==24);
    assert(choose(4,2)==6);
    
    long long n;
    cin >> n;
    vector<long long> arr(n);
    for(long long i=0; i<n; ++i){
    	cin >> arr[i];
    }

    long long ans = 1;
    long long i = 0;
    while(i<n){
    	long long j = i+1;
    	while(j<n && arr[j]>arr[j-1]){
    	    j++;
    	}
	assert(j>i);
	long long d = j-i;
	long long temp2 = 0;
	vector<bool> first_pass(d,true);
	for(long long row = 1; row <= d; ++row){
	    assert(row>=0);
	    long long temp = compute_(d, d, row);
	    printf("seg: [%lld, %lld), d: %lld, row: %lld, compute: %lld\n", i, j, d, row, temp);
	    temp2 = (temp + temp2) % M;
	}

    	// printf("seg: [%lld, %lld), seg compute: %lld\n", i, j, temp2);

	ans = (ans * temp2) % M;
	
        // printf("ans: %lld\n", ans);
	
    	i=j;
    }

    printf("%lld\n",ans);    
    return 0;
}
