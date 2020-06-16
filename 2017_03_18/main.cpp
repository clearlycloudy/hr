#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <fstream>
using namespace std;

void walk( vector< vector<int> > & a, set<int> walked, int current, int start, int count, set<set<int> > & accum ){
    if( count == 3 ){
	if( current == start ){
	    accum.insert( walked );
	    return;
	}else{
	    return;
	}
    }
    if( walked.find(current) != walked.end() ){
	return;
    }
    walked.insert(current);
    for( int next = 0; next < a.size(); ++next ){
	if( (a[current][next] == 1 ) && (current != next) ){
	    walk( a, walked, next, start, count+1, accum);
	}
    }
}

struct node {
    vector<int> vertices;
    int count = 0;
};


class mycomp
{
public:
    bool operator()( node * const & a, node * const & b ) const {
	return a->count > b->count;
    }
};

int main() {
    ifstream in("test2.txt");
    streambuf *inbuf = cin.rdbuf();
    cin.rdbuf(in.rdbuf());    
    int n;
    cin >> n;
    vector< vector<int> > adj_list(n,vector<int>());
    vector< vector<int> > arr(n,vector<int>(n));
    for( int i = 0; i < n; ++i ){
	for( int j = 0; j < n; ++j ){
	    int n;
	    cin >> arr[i][j];
	    if(arr[i][j] == 1)
	    {
		adj_list[i].push_back(j);
	    }
	}
    }
    //discover trigs
    set< set<int> > accum;
    set< int > walked;
    for( int i = 0; i < n; ++i ){
	walk( arr, walked, i, i, 0, accum );
    }
    //collect trigs
    priority_queue< node*, vector<node*>, mycomp > q;
    set<int> trigverts;
    vector<int> count(n,0);
    vector<int> count_adj(n,0);
    int num_trig = 0;
    vector<node*> trigs;
    vector<set<node*> > map_to_trig(n,set<node*>());
    map<node*,bool> seen_node;
    for( auto & i : accum ){
	++num_trig;
	node * n = new node;
	n->count = 0;
	for( auto & j : i ){
	    trigverts.insert(j);
	    ++count[j];
	    n->vertices.push_back(j);
	    map_to_trig[j].insert(n);
	}
	trigs.push_back(n);
	seen_node[n] = false;
    }

    for( auto & i : trigs ){
	for( auto & j : i->vertices ){
	    i->count += count[j];
	}
	q.push(i);
    }

    //degenerate case, early exit
    if( num_trig == 0 ){
	cout << 1 << endl;
	cout << 1 << endl;
	return 0;
    }
    
    vector<bool> seen(n,false);
    while( !q.empty() ){
	double r = num_trig/(double)trigverts.size();
	node * current = q.top();
	seen_node[current] = true;
	q.pop();
	int c = current->count;
	int numer_new = num_trig - 1;
	vector<int> vert_to_remove;
	bool valid = false;
	for( auto ele : current->vertices ){
	    if( count[ele] == 1 ){
		valid = true;
		vert_to_remove.push_back(ele);
	    }
	}
	int denom_new = trigverts.size() - vert_to_remove.size();
	double r_new = numer_new/(double)denom_new;
	
	cout << "vertices: ";
	for( auto & ele : current->vertices ){
	    cout << ele << " ";
	}
	cout << ", numer: " << numer_new << ", denom: " << denom_new << endl;

	if( false == valid ){
	    continue;
	}

	if( r_new < r ){
	    continue;
	}

	//remove trig and decrease count of vertices
        --num_trig;
	for( auto ele : current->vertices ){
	    --count[ele];
	    if( count[ele] == 0 ){
		trigverts.erase(ele);
		cout << "removing vert: " << ele + 1 << endl;
	    }
	    // //update neighbouring count of nearby trigs
	    // for( auto t : map_to_trig[ele] ){
	    // 	if( t != current && seen_node[t] == false ){
	    // 	    node * n_new = new node;
	    // 	    trigs.push_back(n_new);
	    // 	    n_new->vertices = t->vertices;
	    // 	    n_new->count = t->count - 1;
	    // 	    map_to_trig[ele].insert(n_new);
	    // 	    seen_node[n_new] = false;
	    // 	}
	    // }
	}
    }
    
    cout << trigverts.size() << endl;
    for( auto & i : trigverts ){
	cout << i+1 << " ";
    }
    cout << endl;

    cin.rdbuf(inbuf);

    for( auto & i : trigs ){
	delete i;
    }
    return 0;
}
