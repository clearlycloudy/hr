#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

int main() {

    int q;
    cin >> q;
    for(int t=0; t<q; ++t){
	long long n, m;
	cin >> n >> m;
	vector<long long> arr(n);
	for(auto &i: arr){
	    cin >> i;
	    i = i % m;
	}
	for(int i=1;i<n;++i){
	    arr[i] = (arr[i] + arr[i-1]) % m;
	}
	set<long long> seen {};
	long long ans = 0;
	for(int i=0;i<n;++i){
	    auto it = seen.insert(arr[i]);
	    it.first++;
	    long long next_highest = 0;
	    if(it.first!=seen.end()){
		next_highest = *it.first;
	    }
	    ans = max(ans, max(arr[i], (arr[i]-next_highest+m)%m));
	}
	cout << ans << endl;
    }

    return 0;
}
