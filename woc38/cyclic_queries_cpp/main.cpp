#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cassert>

using namespace std;

class node;
class mycomparison;

typedef priority_queue<node,vector<node>, mycomparison> myqueue;

class node {
public:
    int val;
    unsigned time;
    vector<int> inner;
};

class mycomparison
{
public:
    bool operator() (const node& lhs, const node&rhs) const
    {
	if( lhs.val==rhs.val ){
	    return lhs.time < rhs.time;
	} else {
	    return lhs.val < rhs.val;
	}
    }
};

int main() {

    int n;
    cin >> n;
    vector<int> w;

    unsigned t = 0;
    
    vector< myqueue > ext( n, myqueue() );
    for( int i = 0; i < n; i++ ){
	int v;
	cin >> v;
	w.push_back(v);
    }
    vector<int> w_accum = w;
    for( int i = 0; i < n; ++i ){
	w_accum.push_back(w_accum[i]);
    }
    for( int i = 0; i < n; ++i ){
	w_accum.push_back(w_accum[i]);
    }
    for( int i = 1; i < n*3; ++i ){
	w_accum[i] += w_accum[i-1];
    }

    int m;
    cin >> m;
    for( int i = 0; i < m; ++i ){
	int q, x;
	cin >> q >> x;
	x--;
	x += n;
	if( q == 1 ){
	    int weight;
	    cin >> weight;
	    //find the farthest node from x
	    int idx_far = x + n - 1;
	    unsigned t_max = 0;
	    for( int j = x; j < x + n; ++j ){
		int l0 = 0;
		l0 = w_accum[x + n - 2] - w_accum[x-1];
		int l1 = 0;
		if( !ext[j%n].empty() ){
		    l1 = ext[j%n].top().val;
		}
		if(l1 >= l0){
		    if( ext[j%n].top().time > t_max ){
			t_max = ext[j%n].top().time;
			idx_far = j;
		    }
		}
	    }
	    // cout << "farthest node index: " << idx_far % n << endl;
	    if( ext[idx_far % n].empty() ){
		// cout << "ins new node with weight: " << weight << endl;
		node newnode;
		newnode.val = weight;
		newnode.time = ++t;
		newnode.inner.push_back(weight);
		ext[idx_far % n].push( newnode );
		// cout << "ext priority top val: " << ext[idx_far % n].top().val << endl;
	    } else {
		// cout << "ins into existing extension" << endl;
		node curnode = ext[idx_far % n].top();
		ext[idx_far % n].pop();
		curnode.inner.push_back(weight);
		curnode.val += weight;
		curnode.time = ++t;
		ext[idx_far % n].push(curnode);
	    }
	} else if( q == 2 ){
	    int weight;
	    cin >> weight;
	    //add new edge to a new node at x
	    node newnode;
	    newnode.val = weight;
	    newnode.time = ++t;
	    newnode.inner.push_back(weight);
	    ext[x%n].push( newnode );
	} else if( q == 3 ){
	    //find the farthest node from x
	    unsigned t_max = 0;
	    int idx_far = x + n - 1;
	    for( int j = x; j < x + n; ++j ){
		int l0 = 0;
		l0 = w_accum[x + n - 2] - w_accum[x-1];
		int l1 = 0;
		if( !ext[j%n].empty() ){
		    l1 = ext[j%n].top().val;
		}
		if(l1 >= l0){
		    if( ext[j%n].top().time > t_max ){
			t_max = ext[j%n].top().time;
			idx_far = j;
		    }
		}
	    }
	    // cout << "attempting to remove node from farthest node index: " << idx_far % n << endl;
	    //delete the node
	    if( !ext[idx_far%n].empty() ){
		node curnode = ext[idx_far%n].top();
		ext[idx_far%n].pop();
		int back_val = curnode.inner.back();
		curnode.val -= back_val;
		curnode.inner.pop_back();
		ext[idx_far%n].push(curnode);
	    }else{
		assert(false);
	    }
	} else {
	    //find the farthest node from x
	    int idx_far = x + n - 1;
	    unsigned t_max = 0;
	    for( int j = x; j < x + n; ++j ){
		int l0 = 0;
		l0 = w_accum[x + n - 2] - w_accum[x-1];
		int l1 = 0;
		if( !ext[j%n].empty() ){
		    l1 = ext[j%n].top().val;
		}
		if(l1 >= l0){
		    if( ext[j%n].top().time > t_max ){
			t_max = ext[j%n].top().time;
			idx_far = j;
		    }
		}
	    }
	    // cout << "farthest node index: " << idx_far % n << endl;
	    //print the total farthest distance from x
	    int ext_dist = 0;
	    if( !ext[idx_far % n].empty() ){
		ext_dist = ext[idx_far % n].top().val;
	    }
	    int total = w_accum[idx_far-1] - w_accum[x-1] + ext_dist;
	    // cout << "total: " << total << endl;
	    cout << total << endl;
	}
    }
    
    return 0;
}
