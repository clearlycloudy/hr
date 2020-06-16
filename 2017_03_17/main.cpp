#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <set>
#include <map>
using namespace std;

int main() {
    int n,q;
    cin >> n >> q;
    //precompute
    map<int, set<int> > accum;
    for( int j = 0; j < n; ++j ){ //O(nlog(n))
	int i;
	cin >> i;
	auto it = accum.find(i);
	if( it == accum.end()){
	    auto it2 = accum.insert(std::pair<int,set<int> >(i,set<int>()));
	    it = it2.first;
	}
	it->second.insert(j);
    }
    for( int i = 0; i < q; ++i ){ //query.  q <= 4x10E4. O(q)
	int l,r,x,y;
	cin >> l >> r >> x >> y; // y < x <= 4x10E4. l<=r<=a.size()<=4x10E4
	int ans = 0;
	for( auto it = accum.begin(), it_e = accum.end(); it!=it_e; ++it ){
	    auto it_l = it->second.lower_bound(l); //O(log(n)
	    auto it_r = it->second.upper_bound(r); //O(log(n)
	    int dist = std::distance(it_l, it_r);
	    if( y == (it->first % x) ){
		ans += dist;
	    }
	}
	cout << ans<< endl;
    }
    return 0;
}
