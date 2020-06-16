#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;


void visit(long long sum, long long avg, int n, int cur, map<int,set<int>> & adj, vector<int> &accum, vector<int> & arr, set<long long> & lookup, long long & best){
    
    for(auto& i: adj[cur]){
	if(i!=cur){ //guard on cycles

	    //no cut
	    visit(sum, avg, n , cur, adj, accum, arr, lookup, best);

	    //try cut
	    int a = sum - accum[i];
	    int b = accum[i];

	    lookup.insert(a);
	    lookup.insert(b);
	}
    }
    return {true, partition};
}

int main() {

    int q, n;
    cin >> q;
    vector<int> arr(50000);
    vector<int> parent(50000,-1);
	
    for(int i=0;i<q;++i){
        map<int,set<int>> adj;
	cin >> n;
	for(int j=0;j<n;++j){
	    cin >> arr[j];
	}
	for(int j=0;j<n-1;++j){
	    int a,b;
	    cin >> a >> b;
	    a--; b--;
	    adj[a].insert(b);
	    adj[b].insert(a);
	}

	vector<long long> accum(n,0);
	for(int j=0;j<n;++j){
	    accum[j]=arr[j];
	}
	vector<int> queue = {0};
        parent[0] = 0;
        vector<int> visit(n,0);
	visit[0] = 1;
	while(queue.size()>0){
	    int cur = queue.back();
	    cout << "cur: " << cur <<endl;
	    if(visit[cur]==2){
		if(cur!=0){
		    accum[parent[cur]] += accum[cur];
		}
		queue.pop_back();
		continue;
	    }
	    cout << "cur state:1"<<endl;
	    for(auto&j: adj[cur]){
		if(visit[j]==0){
		    visit[j]=1;
		    queue.push_back(j);
		    parent[j]=cur;
		}
	    }
	    visit[cur]=2;
	}
	// for(auto &j: accum){
	//     cout << j << " ";
	// }
	// cout << endl;

	long long avg = accum[0]/3 + ((accum[0]%3)==0 ? 0 : 1);
	long long best = 1999999999;

	long long sum = accum[0];
        set<long long> lookup;
	visit(sum, avg, n, 0, adj, accum, arr, lookup, best);
    }    
    
    return 0;
}
