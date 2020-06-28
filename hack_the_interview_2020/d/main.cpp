#include <bits/stdc++.h>

using namespace std;

struct dsu {
    int id;
    dsu * repr;
    int count;
    dsu(int i){
	id = i;
	repr = this;
	count = 1;
    }
    dsu * find(){ //path compression
	if(repr!=this){
	    repr = repr->find();
	}
	return repr;
    }
    int get_id(){
	dsu * r = this->find();
	return r->id;
    }
    dsu * add(dsu * other){
	dsu * r = this->find();
	dsu * o = other->find();
	assert(r);
	assert(o);
	return r->merge(o);
    }
    dsu * merge(dsu * other){
	if(count >= other->count){
	    other->repr = this;
	    count += other->count;
	    return this;
	}else{
	    repr = other;
	    other->count += count;
	    return other;
	}
    }
};
    
int main() {
    int n;
    cin >> n;
    vector<dsu*> xs(n);
    for(int h=0; h<n; ++h){
	xs[h] = new dsu(h);
    }
    vector<int> con(n);
    vector<int> incoming_count(n,0);
    for(int h=0; h<n; ++h){
    	int to;
	cin >> to;
        to--;
        xs[to]->add(xs[h]);
	con[h] = to;
	incoming_count[to]++;
    }

    set<int> components;
    map<int,bool> component_cycle;
    
    for(auto i: xs)
	components.insert(i->get_id());
    
    for(auto i: components)
	component_cycle[i] = false;

    set<int> leaves;
    for(int h=0; h<n; ++h){
	if(incoming_count[h]==0){
	    leaves.insert(h);
	}
    }
    vector<int> q(leaves.begin(), leaves.end());
    for(int h=0; h<n; ++h){
	if(leaves.find(h)==leaves.end()){
	    q.push_back(h);
	}
    }
    //check_cycles
    vector<bool> visited(n, false);
    for(auto h: q){
	xs[h]->find();//path compression
	int component_id = xs[h]->get_id();
        if(!visited[h]){
	    int cur = h;
	    visited[cur] = true;
	    int to = con[cur];
	    set<int> path {cur};
	    while(1){
		if(visited[to]){
		    if(to!=cur && path.find(to) != path.end()){
			//not a self cycle
			component_cycle[component_id] = true;
		    }
		    break;
		}else{
		    path.insert(to);
		    visited[to] = true;
		    cur = to;
		    to = con[cur];
		}
	    }
	}
    }

    int count_cycle = 0;
    for(auto [comp, cycle] : component_cycle){
    	// cout << comp << ": " << cycle << endl;
	if(cycle) count_cycle++;
    }
    int count_total = component_cycle.size();
    int count_non_cycle = count_total - count_cycle;

    int ans = count_cycle + max(count_non_cycle-1,0);
    cout << ans << endl;
    
    for(auto i: xs)
	delete i;
}
