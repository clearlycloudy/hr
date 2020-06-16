#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;

struct node{
    int parent;
    int level;
    int id;
    int dist_to_u;
    vector<int> children;
    node(){
	parent = -1;
	level = 0;
	dist_to_u = -1;
    }
};

int find_dist_lca( vector<node> & nodes, node * n1, node * n2 ){
    node * dest = n2;
    bool start_at_dest;
    //find least common ancestor
    int min_level = min( n1->level, n2->level );
    if( n1->level > n2->level ){
	swap( n1, n2 );
    }
    //now n2 has the max level
    if( n2 == dest ){
	start_at_dest = true;
    }else{
	start_at_dest = false;
    }
    int dist = 0;
    list<node*> path {};
    while( n2->level > min_level ){
	path.push_back(n2);
	node * n2_prev = n2;
	n2 = &nodes[n2->parent];
	++dist;
    }
    int dist2 = 0;
    list<node*> path2{};
    // if( n1 != n2 && start_at_dest ){
    // 	if( nodes[n1->parent].dist_to_u != -1 ){
    // 	    n1->dist_to_u = nodes[n1->parent].dist_to_u + 1;
    // 	    // cout << n1->id << "retrieve prev computation: final dist: " << n1->dist_to_u << endl;
    // 	    return n1->dist_to_u;
    // 	}
    // }else if( n1 != n2 ){
    // 	if( nodes[n2->parent].dist_to_u != -1 ){
    // 	    n2->dist_to_u = nodes[n2->parent].dist_to_u + dist + 1;
    // 	    // cout << n2->id << "retrieve prev computation: final dist: " << n2->dist_to_u << endl;
    // 	    return n2->dist_to_u;
    // 	}
    // }else if( n1 == n2 && start_at_dest ){
    // 	n1->dist_to_u = dist;
    // 	return n1->dist_to_u;
    // }else if( n1 == n2 && !start_at_dest ){
    // 	n2->dist_to_u = dist;
    // 	return n2->dist_to_u;
    // }

    while( n1 != n2 ){
	path.push_back(n2);
	path2.push_back(n1);
	n2 = &nodes[n2->parent];
	n1 = &nodes[n1->parent];
	dist2 += 2;
    }
    path2.push_back(n1);
    //save computation for nodes on current path
    // cout << "save computation. dist: " << dist + dist2 << endl;
    list<node*> list_temp;
    if( start_at_dest ){
	path.reverse();
	path2.splice(path2.end(),path);
	list_temp = move(path2);
    }else{
	path2.reverse();
	path.splice(path.end(),path2);
	list_temp = move(path);
    }
    // int temp_dist = dist + dist2;
    // for( auto & i : list_temp ){
    // 	cout << i->id << " ";
    // 	i->dist_to_u = temp_dist;
    // 	--temp_dist;
    // }
    // cout << endl;
    
    return dist + dist2;
}

int main() {
    int n;
    cin >> n;
    vector<node> nodes(n);
    nodes[0].id = 0;
    for( int i = 1; i < nodes.size(); ++i ){
	int parent;
	cin >> parent;
	--parent;
	nodes[i].parent = parent;
	nodes[parent].children.push_back(i);
	nodes[i].id = i;
    }
    {
	queue<int> q{};
	q.push(0);
	while(!q.empty()){
	    node * n = &nodes[q.front()];
	    q.pop();
	    for( auto & i : n->children ){
		nodes[i].level = n->level + 1;
		q.push(i);
	    }
	}
    }
    // cout << "level: " << endl;
    // for( auto & i : nodes ){
    // 	cout << i.level << endl;
    // }

    int q;
    cin >> q;
    for( int i = 0; i < q; ++i ){
	int u, v;
	cin >> u >> v;
	int dist = 0;
	node * n_u = &nodes[u-1];
	queue<int> set_v{};
	set_v.push(v-1);
	// list<int> to_visit {};
	while(!set_v.empty()){
	    node * n_v = &nodes[set_v.front()];
	    set_v.pop();
	    // to_visit.push_back(set_v.front());
	    for( auto & h : n_v->children ){
		set_v.push( h );
	    }
	    int pair_dist = find_dist_lca( nodes, n_v, n_u );
	    // cout << "pair dist: " << pair_dist << endl;
	    dist += (pair_dist * pair_dist);
	}
	cout << dist << endl;
    }
    return 0;
}
