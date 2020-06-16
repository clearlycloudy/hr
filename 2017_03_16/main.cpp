#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
using namespace std;


long get_stack_cost( vector<long> & accum_cost, vector<long> & accum_w, vector<long> & dist, int current, int prev ){
    if( prev >= accum_cost.size() ){
	return accum_cost[current];
    }
    long cost = accum_cost[current] - accum_cost[prev];
    cost -= accum_w[prev] * (dist[prev] - dist[current]);
    return cost;
}

void arrange( vector<long>& accu_cost, vector<long>& accu_w, vector<long>& alt, int i, int prev, int k, long accum, long & best ){
    if( k == 1 ){
	long cost = get_stack_cost( accu_cost, accu_w, alt, 0, prev );
	accum += cost;
        if( accum < best )
            best = accum;
        return;
    }
    if( i < 0 )
	return;
    //choose not to stack at current position
    arrange( accu_cost, accu_w, alt, i-1, prev, k, accum, best);

    //choose to stack at current position
    long stack_cost = get_stack_cost( accu_cost, accu_w, alt, i, prev );
    accum += stack_cost;
    if( accum < best ){
	arrange( accu_cost, accu_w, alt, i-1, i, k-1, accum, best);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n,k;
    cin >> n >> k;
    vector<int> weight(n);
    vector<long> alt(n);
    for( int i = 0; i < n; ++i ){
        cin >> alt[i];
        cin >> weight[i];
    }    
    vector<long> accu_cost(n,0);
    vector<long> accu_w(n,0);
    //precompute cost
    long w = 0;
    if(n>=1){
        w = weight[n-1];
	accu_w[n-1] = w;
    }
    for( int i = n-2; i >= 0; --i ){
	long delta = alt[i+1]-alt[i];
        accu_cost[i] = accu_cost[i+1] + w*delta;
        w += weight[i];
	accu_w[i] = w;
    }
    
    // //debug only starts
    // cout << "accum accu_cost: " << endl;
    // for( auto & i : accu_cost ){
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << "accumulated weight: " << endl;
    // for( auto & i : accu_w ){
    //     cout << i << " ";
    // }
    // cout << endl;
    // //debug only ends

    // long best = std::numeric_limits<long>::max();
    // arrange( accu_cost, accu_w, alt, n-1, n, k, 0, best );
    // cout << "recursive ans: " << best << endl;

    //stack cost table
    vector<vector<long> >cost_table(n, vector<long>(n+1, std::numeric_limits<long>::max()) );
    for( int i = 0; i < n; ++i ){
    	for( int j = i+1; j <= n; ++j ){
    	    cost_table[i][j] = get_stack_cost( accu_cost, accu_w, alt, i, j );
    	}
    }

    // //debug only
    // cout << "cost table: " << endl;
    // for( int i = 0; i < n; ++i ){
    // 	for( int j = 0; j <= n; ++j ){
    // 	    if( cost_table[i][j] != std::numeric_limits<long>::max() )
    // 		cout << cost_table[i][j] << " ";
    // 	    else
    // 		cout << "-- ";
    // 	}
    // 	cout << endl;
    // }

    //init dp
    vector< long > dp(n, std::numeric_limits<long>::max() );
    vector< long > dp_prev_k(n, std::numeric_limits<long>::max() );
    for( int i = 0; i < n; ++i ){
	// dp_prev_k[i] = get_stack_cost( accu_cost, accu_w, alt, i, n );
	dp_prev_k[i] = cost_table[i][n];
    }
    //main algo. O(k*(n-2k)*(n-k))
    for( int m = 2; m <= k; ++m ){ //O(k)
	for( int i = n-m+1; i > (k-m); --i ){ //O(n-2k)
	    for( int j = i-1; j >= (k-m); --j ){ //O(n-k)
		long prev = dp_prev_k[i];
		// long c = get_stack_cost( accu_cost, accu_w, alt, j, i );
		long c = cost_table[j][i];
		if( prev != std::numeric_limits<long>::max() && c != std::numeric_limits<long>::max()){
		    long s = c + prev;
		    if( s < dp[j] )
			dp[j] = s;
		}
	    }
	}
	dp.swap( dp_prev_k );
	for( auto & ele : dp ){
	    ele = std::numeric_limits<long>::max();
	}
    }

    // //debug only
    // cout << "dp table: " << endl;
    // for( auto & i : dp ){
    // 	for( auto & j : i ){
    // 	    if( j != std::numeric_limits<long>::max() )
    // 		cout << j << " ";
    // 	    else
    // 		cout << "--" << " ";
    // 	}
    // 	cout << endl;
    // }

    if( k == 0)
	cout << 0 << endl;
    else
	cout << dp_prev_k[0] << endl;
    // //debug only
    // assert( dp[0][k] == best );

    return 0;
}
