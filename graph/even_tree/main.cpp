#include <iostream>
#include <vector>
using namespace std;

int main() {


    int n,e;
    cin >>n>>e;

    vector< vector<int> > v_c(n+1, vector<int>{} );
    vector< int > done(n+1, false );
    
    for( int i = 0; i < n; ++i ){
	int f,t;
	cin >> f >> t;
	v_c[f].push_back(t);
	v_c[t].push_back(f);
    }
    
    vector<int> q {1};

    vector< vector<int> > g(n+1, vector<int>{} );
    vector< int > p(n+1);    
    done[1] = 1;

    while (!q.empty()) {
	int a = q.back();
	q.pop_back();
        for( auto i : v_c[a] ) {
            if (done[i] == 0 ){
                g[a].push_back(i);
                p[i] = a;
                done[i] = 1;
                q.push_back(i);
            }
        }
    }

    q.clear();
    q.push_back(1);

    vector<int> parity(n+1,1);
    for( auto & i : done ){
        i = 0;
    }

    int cuts = 0;
    while( !q.empty() ) {
	int a = q.back();
        if(!done[a]) {
            for( auto i : g[a]) {
                q.push_back(i);
            }
            done[a] = 1;
        } else {
            parity[ p[a] ] += parity[a];
            if( parity[a] % 2 == 0 ){ //cut if subtree is even
                cuts += 1;
            }
            q.pop_back();
        }
    }
    cout << cuts - 1 << endl;
}
