#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <cassert>

using namespace std;
int main () {

    int n;
    cin >> n;
    vector<long> arr;
    for( int i = 0; i < n; ++i ){
	int v;
	cin >> v;
	arr.push_back(v);
    }
    
    unordered_map<long int, vector<unsigned> > hm;

    unsigned long int pown = pow(2,n);

    for( unsigned i = 1; i < pown; ++i ) {
        unsigned j = i;
	int index = 0;
        long int sum = 0;
	while( j != 0 ){
	    if( j & 0x01 > 0 ){
		assert(index < n );
	        long int val = arr[index];
		sum += val;
	    }
	    j = j >> 1;
	    index += 1;
	}
	if(hm.find(sum) == hm.end()) {
	    hm[sum] = {};
	}
	hm[sum].push_back(i);
    }

    long triplets = 0;
    for( auto & i : hm ) {
	auto & v = i.second;
	int l = v.size();
	for( int a = 0; a < l; a++ ){
	    for( int b = a+1; b < l; b++ ) {
		for( int c = b+1; c < l; c++ ) {
		    if ( ((v[a] & v[b]) == 0 )&&
			 ((v[b] & v[c]) == 0 )&&
			 ((v[a] & v[c]) == 0 )&&
			 ((v[a]^v[b]^v[c]) == pown -1) ) {
			    triplets++;
		    }
		}
	    }
	}
    }

    cout << triplets * 6 << endl;
}
